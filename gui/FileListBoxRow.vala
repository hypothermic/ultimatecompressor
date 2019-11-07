using GLib;

using Gtk;
using Gdk;

public class UC.FileListBoxRow : Gtk.ListBoxRow {

    private string file_path;

    public FileListBoxRow(string file_path) {
        this.file_path = file_path;
        stderr.printf("Added file: %s\n", file_path);

        Gtk.Label label = new Gtk.Label(file_path);
        label.margin_top = 8;
        label.margin_bottom = 8;
        this.add(label);
    }
}