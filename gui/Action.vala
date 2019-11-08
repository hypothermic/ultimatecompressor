using GLib;

/**
 * This is actually a class-based enum, because Vala enums suck.
 */
public class UC.Action : GLib.Object {

    public static UC.Action COMPRESS   = new UC.Action("Compress");
    public static UC.Action DECOMPRESS = new UC.Action("Decompress");

    public static void init() {
        new UC.Action("no-op");
    }

    private string name;

    [CCode (construct_function = null)]
    private Action(string name) {
        this.name = name;
    }

    public string get_name() {
        return name;
    }
}