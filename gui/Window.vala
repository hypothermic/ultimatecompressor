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