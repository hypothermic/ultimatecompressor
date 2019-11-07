using GLib;

/**
 * An alternative ArrayList implementation, similar to Java.<br /> <br />
 *
 * TODO implement List.
 */
public class UC.ArrayList<G> : GLib.Object {

    /**
     * Counts how many objects were added to the <i>array</i>.<br /><br />
     *
     * This is not the same as array.length!
     */
    private int count = 0;
    private G[] array = new G[0];

    public void add(G object) {
        if (array.length < ++count) {
            array.resize(count);
        }
        array[count-1] = object;
    }
}