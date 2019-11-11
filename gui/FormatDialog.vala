using GLib;

using Gtk;
using Gdk;

using UC;
using UltimateCompressor;
using UltimateCompressor.Archive;

/**
 * A dialog which presents the user with options regarding the archive format enum.
 */
[GtkTemplate (ui = "/nl/hypothermic/ultimatecompressor/gui/dialog_format.glade")]
public class UC.FormatDialog : /*UC.AbstractDialog<Archive.Format>*/ Gtk.Dialog {

    [GtkChild (name="main-container", internal="true")]
    private Gtk.Box main_container;

    [GtkChild (name="main-box", internal="true")]
    private Gtk.ButtonBox main_box;

    [GtkChild (name="content-container", internal="true")]
    private Gtk.Box content_container;

    [GtkChild (name="content-title-wrapper", internal="true")]
    private Gtk.Box content_title_wrapper;

    [GtkChild (name="content-title", internal="true")]
    private Gtk.Label content_title;

    [GtkChild (name="content-action-cancel", internal="true")]
    private Gtk.Button content_action_cancel;

    [GtkChild (name="content-action-accept", internal="true")]
    private Gtk.Button content_action_accept;

    private UC.DialogCallback<Archive.Format> callback;
    private bool is_finished = false;

    static construct {
        //UltimateCompressor.init();
    }

    public FormatDialog(UC.DialogCallback<Archive.Format> callback) {
        this.callback = callback;
    }

    protected void finish(Archive.Format object, UC.DialogAction action) {
        if (!is_finished) {
            is_finished = true;
            callback(object, action);
        }
    }

	[GtkCallback (name="window_close_cb")]
    private void window_close_cb() {

    }

    [GtkCallback (name="window_response_cb")]
    private void window_response_cb() {

    }

	[GtkCallback (name="window_destroy_cb")]
    private void window_destroy_cb() {

	}

    [GtkCallback (name="window_show_cb")]
	private void window_show_cb() {
	    Gtk.CssProvider css_provider = new Gtk.CssProvider();
	    unowned Gdk.Screen? current_screen = Gdk.Screen.get_default();
	    if (current_screen != null) {
        	css_provider.load_from_resource("/nl/hypothermic/ultimatecompressor/gui/dialog_format.css");
            Gtk.StyleContext.add_provider_for_screen((Gdk.Screen) current_screen, css_provider, Gtk.STYLE_PROVIDER_PRIORITY_APPLICATION);
	    }
	}

    [GtkCallback (name="action_cancel_cb")]
	private void action_cancel_cb() {

	}

    [GtkCallback (name="action_accept_cb")]
	private void action_accept_cb() {

	}
}