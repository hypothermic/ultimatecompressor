using GLib;

using Gtk;
using Gdk;

[GtkTemplate (ui = "/nl/hypothermic/ultimatecompressor/gui/window.ui")]
public class UC.Window : Gtk.Window {

    [GtkChild (name="main-container", internal="true")]
    private Gtk.Box main_container;

    [GtkChild (name="content-container", internal="true")]
    private Gtk.Box content_container;

    [GtkChild (name="content-title", internal="true")]
    private Gtk.Label content_title;

    [GtkChild (name="content-file-list", internal="true")]
    private Gtk.ListBox content_file_list;

    [GtkChild (name="content-file-chooser", internal="true")]
    private Gtk.FileChooserButton content_file_chooser;

    [GtkChild (name="content-action-container", internal="true")]
    private Gtk.Box content_action_container;

    [GtkChild (name="content-action-compress", internal="true")]
    private Gtk.Button content_action_compress;

    [GtkChild (name="content-action-decompress", internal="true")]
    private Gtk.Button content_action_decompress;

    private UC.ArrayList<UC.FileListBoxRow> list_rows = new UC.ArrayList<UC.FileListBoxRow>();

    construct {
        UC.FileListBoxRow row = new UC.FileListBoxRow("My Files");
        content_file_list.insert(row, -1);
    }

	[GtkCallback]
    private void window_destroy_cb() {
		Gtk.main_quit();
	}

	[GtkCallback]
	private void action_file_set_cb() {
        UC.FileListBoxRow row = new UC.FileListBoxRow(content_file_chooser.get_filename());
        list_rows.add(row);
        content_file_list.insert(row, -1);
	}

    [GtkCallback]
	private void window_show_cb() {
	    Gtk.CssProvider css_provider = new Gtk.CssProvider();
	    try {
	        css_provider.load_from_resource("/nl/hypothermic/ultimatecompressor/gui/window.css");
            Gtk.StyleContext.add_provider_for_screen(Gdk.Screen.get_default(), css_provider, Gtk.STYLE_PROVIDER_PRIORITY_USER);
        } catch (Error error) {
            stderr.printf("A resource could not be loaded: %s\n", error.message);
        }
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