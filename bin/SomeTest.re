let div = (~children=[""], _, ~href) => {
  switch (children) {
  | [""] => href
  | rest =>
    href
    ++ List.fold_left(
         (a, b) => a ++ "," ++ b,
         List.hd(rest),
         List.tl(rest),
       )
  };
};
let add = (~children=[0], _, ~left, ~right) => {
  switch (children) {
  | [] => left + right
  | [a, ..._] => left + right + a
  };
};
let toString = (~children, _) =>
  switch (children) {
  | _ =>
    string_of_int(
      List.fold_left(
        (a, b) => a + b,
        List.hd(children),
        List.tl(children),
      ),
    )
  };
let make = <add left=1 right=2> <add left=1 right=2 /> </add>;
let ret =
  <div href="1 ">
    <toString> <add left=3 right=4 /> <add left=32 right=4 /> </toString>
  </div>;

print_int(make);
print_newline();
print_endline(ret);
Lwt.bind(Lwt_io.read_line(Lwt_io.stdin), str =>
  Lwt_io.printlf("You typed %S", str)
);

let eea =
  "somestring"
  |> String.to_seq
  |> Seq.map((c) => "+"++String.make(1, c)++"+")
  |> List.of_seq
  |> String.concat("!")

let result = [|1, 2, 3|]
  |> Array.map(a => a + 1)
  |> Array.exists(a => a mod 2 === 0);

Console.log(result)
print_endline(eea)
