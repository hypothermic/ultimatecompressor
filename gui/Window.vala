using GLib;

using Gtk;
using Gdk;

[GtkTemplate (ui = "/nl/hypothermic/ultimatecompressor/gui/window.ui")]
public class UC.Window : Gtk.Window {

	construct {

	}

	[GtkCallback]
    private void window_destroy_cb() {
		Gtk.main_quit();
	}
}

public static void uc_vala_main(string[] args) {
    Environment.set_application_name("UltimateCompressor");
    Environment.set_prgname("UltimateCompressor");

    if (!Thread.supported()) {
        stderr.printf("Multithreading not supported, the application performance might decrease.\n");
    }

    Gtk.init(ref args);

    UC.Window window = new UC.Window();
    window.show_all();

    Gtk.main();
}