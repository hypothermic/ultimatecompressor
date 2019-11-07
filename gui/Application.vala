using GLib;
using LuDB;

using Gtk;
using UC;

public static int main(string[] args) {
	Environment.set_application_name("UltimateCompressor");
	Environment.set_prgname("UltimateCompressor");

	if (!Thread.supported()) {
        stderr.printf("Multithreading not supported, the application performance might decrease.\n");
    }

	Gtk.init(ref args);

	Window window = new Window();
	window.show_all();

	Gtk.main();

	return(0);
}