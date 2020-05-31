let counter = ref(0)
let listen_address = Unix.inet_addr_loopback
let port = 9000
let backlog = 10
let handle_message = msg =>
  switch (msg) {
  | "read" => string_of_int(counter^)
  | "inc" =>
    counter := counter^ + 1;
    "Counter has been incremented";
  | _ => "Unknown command"
  };

let rec handle_connection = (ic, oc, ()) =>
  Lwt.(
    Lwt_io.read_line_opt(ic) >>= (
      msg =>
        switch (msg) {
        | Some(msg) =>
          let reply = handle_message(msg);
          Lwt_io.write_line(oc, reply) >>= handle_connection(ic, oc);
        | None =>
          print_endline("Connection closed");
          return();
        }
    )
  );

  let accept_connection = conn => {
    let (fd, _) = conn;
    let ic = Lwt_io.of_fd(~mode=Lwt_io.Input, fd);
    let oc = Lwt_io.of_fd(~mode=Lwt_io.Output, fd);
    Lwt.on_failure(handle_connection(ic, oc, ()), e =>
      print_endline(Printexc.to_string(e))
    );
    print_endline("New connection")
    Lwt.return();
  };

let create_server = sock => {
    let (>>=) = Lwt.(>>=)
    let rec serve = () =>
      Lwt_unix.accept(sock) >>= accept_connection >>= serve
    serve
}

let create_socket = () => {
  open Lwt_unix;
  let sock = socket(PF_INET, SOCK_STREAM, 0);
  let addr = [@implicit_arity] ADDR_INET(listen_address, port);
  let _ = bind(sock, addr)
  listen(sock, backlog);
  sock;
};

let telnetServer () = {
  let sock = create_socket();
  let serve = create_server(sock);
  Lwt_main.run @@ serve();
}