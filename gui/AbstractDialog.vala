using GLib;

using Gtk;
using Gdk;

using UC;
using UltimateCompressor;
using UltimateCompressor.Archive;

/**
 * An abstract class to store all common attributes of UC dialogs.
 */
public abstract class UC.AbstractDialog<G> : Gtk.Dialog {

    /**
     * This callback will be called once the action has been completed (finish() has been called).
     */
    private UC.DialogCallback<G> callback;

    /**
     * To prevent from executing the callback multiple times,
     * this field will be set to TRUE and all other finish() calls will be blocked.
     */
    private bool is_finished = false;

    protected AbstractDialog(UC.DialogCallback<G> callback) {
        this.callback = callback;
    }

    /**
     * This method will be called to inform the owner that this dialog has finished.
     */
    protected void finish(G object, UC.DialogAction action) {
        if (!is_finished) {
            is_finished = true;
            callback(object, action);
        }
    }
}