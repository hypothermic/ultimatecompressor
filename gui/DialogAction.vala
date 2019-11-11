using GLib;

public delegate void UC.DialogCallback<G>(G object, DialogAction action);

/**
 * To avoid index conflicts and properly compare dialogactions, we will use an int-based enum.
 */
public enum UC._InternalDialogActionIndex {
    IDX_ACCEPT,
    IDX_CANCEL
}

/**
 * Dialog Actions return the state of a dialog.<br /><br />
 *
 * This is actually a class-based enum, because Vala enums suck.
 */
public class UC.DialogAction : GLib.Object {

    public static UC.DialogAction ACCEPT = new UC.DialogAction(UC._InternalDialogActionIndex.IDX_ACCEPT, "Accept");
    public static UC.DialogAction CANCEL = new UC.DialogAction(UC._InternalDialogActionIndex.IDX_CANCEL, "Cancel");

    public static void init() {
        new UC.DialogAction(UC._InternalDialogActionIndex.IDX_ACCEPT, "no-op");
    }

    private UC._InternalDialogActionIndex enum_entry;
    private string name;

    [CCode (construct_function = null)]
    private DialogAction(UC._InternalDialogActionIndex enum_entry, string name) {
        this.enum_entry = enum_entry;
        this.name = name;
    }

    public string get_name() {
        return name;
    }

    public bool equals(UC.DialogAction action) {
        return this.enum_entry == action.enum_entry;
    }
}