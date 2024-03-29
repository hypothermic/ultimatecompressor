using GLib;

/**
 * An alternative ArrayList implementation, similar to Java.<br /><br />
 *
 * The difference between this and Gee's ArrayList is the signals and count of user actions.<br /><br />
 *
 * TODO implement List.
 */
public class UC.ArrayList<G> : GLib.Object {

    public signal void added(G object);

    /**
     * Counts how many objects were *added* to the <i>array</i>.<br /><br />
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
        added(object);
    }

    /**
     * Calls the delegate for each element in the array, passing the element.
     *
     * ```vala
     * list_rows.iterate((row) => {
     *     stderr.printf("HELLOWORLD");
     * });
     * ```
     */
    public void iterate(Callback<G> on_element) {
        foreach (G element in array) {
            on_element(element);
        }
    }

    /**
     * Returns the amount of elements which were *added to* the array.<br /><br />
     *
     * This may not be the same as the size of the underlying array!
     */
    public int size() {
        return count;
    }
}