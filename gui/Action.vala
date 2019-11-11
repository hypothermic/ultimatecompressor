using GLib;

/**
 * To avoid index conflicts and properly compare actions, we will use an int-based enum.
 */
public enum UC._InternalActionIndex {
    IDX_COMPRESS,
    IDX_DECOMPRESS
}

/**
 * This is actually a class-based enum, because Vala enums suck.
 */
public class UC.Action : GLib.Object {

    public static UC.Action COMPRESS   = new UC.Action(UC._InternalActionIndex.IDX_COMPRESS, "Compress");
    public static UC.Action DECOMPRESS = new UC.Action(UC._InternalActionIndex.IDX_DECOMPRESS,"Decompress");

    public static void init() {
        new UC.Action(UC._InternalActionIndex.IDX_COMPRESS, "no-op");
    }

    private UC._InternalActionIndex enum_entry;
    private string name;

    [CCode (construct_function = null)]
    private Action(UC._InternalActionIndex enum_entry, string name) {
        this.enum_entry = enum_entry;
        this.name = name;
    }

    public string get_name() {
        return name;
    }

    public bool equals(UC.Action action) {
        return this.enum_entry == action.enum_entry;
    }
}