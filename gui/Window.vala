using GLib;

using Gtk;
using Gdk;

using UC;
using UltimateCompressor;
using UltimateCompressor.Archive;

/**
 * The main window which shows an interactive file input list and buttons with compress/decompress.
 */
[GtkTemplate (ui = "/nl/hypothermic/ultimatecompressor/gui/window.glade")]
public class UC.Window : Gtk.Window {

    [GtkChild (name="main-container", internal="true")]
    private Gtk.Box main_container;

    [GtkChild (name="content-container", internal="true")]
    private Gtk.Box content_container;

    [GtkChild (name="content-title-wrapper", internal="true")]
    private Gtk.Box content_title_wrapper;

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

    /**
     * The path to the target output destination.

     TODO UN-HARDCODE AFTER TESTING
     */
    private File? output_file = File.new_for_path("out.zip");

    static construct {
        UltimateCompressor.init();
    }

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
        action_perform(UC.Action.COMPRESS);
	}

    [GtkCallback (name="action_decompress_cb")]
	private void action_decompress_cb() {
        action_perform(UC.Action.DECOMPRESS);
	}

	private void action_perform(UC.Action action) {
	    // If no input file(s) are specified, do not proceed.
        if (list_rows.size() < 1) {
            // TODO display err in GUI
            stderr.printf("No input files specified, not proceeding with %s!\n", action.get_name());
            return;
        }

        // If output path is not specified, do not proceed.
        if (output_file == null) {
            // TODO display err in GUI
            stderr.printf("No output path specified, not proceeding with %s!\n", action.get_name());
            return;
        }

        stderr.printf("Performing %s, %d\n", action.get_name(), Archive.Format.ZIP.is_supported() ? 1 : 69);

        // Try to determine format from destination file name or show dialog.
        if (action.equals(UC.Action.COMPRESS)) {
            Archive.Format? determined_format = Archive.Format.determine_from_file(((!) output_file));
            if (determined_format == null) {
                stderr.printf("No output format auto-determined for %s, querying user.\n", ((!) output_file).get_uri());

                new FormatDialog((archive, action) => {
                    // Check if user cancelled the dialog.
                    if (action.equals(UC.DialogAction.CANCEL)) {
                        stderr.printf("Format query cancelled by user.\n");
                        return;
                    }
                    determined_format = archive;

                    // TODO do compress
                }).show_all();

                return;
            } else {
                stderr.printf("Output format automatically determined: %s\n", ((Archive.Format) determined_format).name);
                // TODO do compress
                return;
            }
        }

        // Try to determine format from input file name or show dialog.
        if (action.equals(UC.Action.DECOMPRESS) && list_rows.size() == 1) {
            stderr.printf("TODO action.perform() decompress single\n"); // TODO
        }

        // Multiple input files!!! Try to determine or show dialog for each input file.
        if (action.equals(UC.Action.DECOMPRESS) && list_rows.size() > 1) {
            stderr.printf("TODO action.perform() decompress multiple\n"); // TODO
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