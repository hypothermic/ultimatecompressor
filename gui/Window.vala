using GLib;

using Gtk;
using Gdk;

using UC;

/**
 * The main window which shows an interactive file input list and buttons with compress/decompress.
 */
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

    /**
     * The list which contains all the rows shown in content_file_list.
     */
    private UC.ArrayList<UC.FileListBoxRow> list_rows = new UC.ArrayList<UC.FileListBoxRow>();

    construct {
        list_rows.added.connect((row) => {
            content_file_list.insert(row, -1);
            content_file_list.show_all();
        });
    }

	[GtkCallback (name="window_destroy_cb")]
    private void window_destroy_cb() {
		Gtk.main_quit();
	}

	[GtkCallback (name="action_file_set_cb")]
	private void action_file_set_cb() {
	    string? filename = content_file_chooser.get_filename();
	    if (filename != null) {
            UC.FileListBoxRow row = new UC.FileListBoxRow((string) filename);
            list_rows.add(row);
	    }
	}

    [GtkCallback (name="window_show_cb")]
	private void window_show_cb() {
	    Gtk.CssProvider css_provider = new Gtk.CssProvider();
	    unowned Gdk.Screen? current_screen = Gdk.Screen.get_default();
	    if (current_screen != null) {
        	css_provider.load_from_resource("/nl/hypothermic/ultimatecompressor/gui/window.css");
            Gtk.StyleContext.add_provider_for_screen((Gdk.Screen) current_screen, css_provider, Gtk.STYLE_PROVIDER_PRIORITY_APPLICATION);
	    }
	}

    [GtkCallback (name="action_compress_cb")]
	private void action_compress_cb() {
        action_perform();
	}

    [GtkCallback (name="action_decompress_cb")]
	private void action_decompress_cb() {
        action_perform();
	}

	private void action_perform() {
        stderr.printf("Performing %s\n", UC.Action.COMPRESS.get_name());
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