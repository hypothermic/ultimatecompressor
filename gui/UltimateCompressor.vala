namespace UltimateCompressor {

    public const string APP_NAME = "UltimateCompressor";
    public const string UC_GUI_VERSION = "1.0.0";
    public const string UC_GUI_BUILD   = "0017";

    public void init() {
        Archive.Format.init();
        UC.Action.init();
    }

// We would not want to generate the main method if we are calling it from another program.
// Enable this from CMake: add_definitions(-DGENERATE_MAIN_METHOD);
#if GENERATE_MAIN_METHOD
    public static int main(string[] args) {
    	Environment.set_application_name("UltimateCompressor");
    	Environment.set_prgname("UltimateCompressor");

    	if (!Thread.supported()) {
            stderr.printf("Multithreading not supported, the application's performance might decrease.\n");
        }

    	Gtk.init(ref args);

    	Window window = new Window();
    	window.show_all();

    	Gtk.main();

    	return(0);
    }
#endif

}