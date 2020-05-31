open GMain;
open GdkKeysyms;
let locale = GtkMain.Main.init();
let main () = {
  let window =
    GWindow.window(
      ~width=320,
      ~height=240,
      ~title="Simple lablgtk program",
      (),
    );
  let vbox = GPack.vbox(~packing=window#add, ());
  let _ = window#connect#destroy(~callback=Main.quit);

  /* Menu bar */
  let menubar = GMenu.menu_bar(~packing=vbox#pack, ());
  let factory = (new GMenu.factory)(menubar);
  let accel_group = factory#accel_group;
  let file_menu = factory#add_submenu("File");

  /* File menu */
  let factory = (new GMenu.factory)(file_menu, ~accel_group);
  let _ = factory#add_item("Quit", ~key=_Q, ~callback=Main.quit);
  /* Info menu */
  let info_menu = factory#add_submenu("Info")
  let factory = new GMenu.factory(info_menu, ~accel_group)
  let _ = factory#add_item("About")

  /* Button */
  let button = GButton.button(~label="Push me!", ~packing=vbox#add, ());
  let _ = button#connect#clicked(~callback=() => prerr_endline("Ouch!"));

  /* Display the windows and enter Gtk+ main loop */
  window#add_accel_group(accel_group);
  window#show();
  Main.main();
};
