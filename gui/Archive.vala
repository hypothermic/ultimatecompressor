using GLib;
using UC;

/*
 * Vala doesn't have macro's so we have to define each individual function for each archive format....
 *
 * Fuck you Vala!
 */

namespace UltimateCompressor {

    /**
     * The namespace with API bindings for `uc_arc_*` methods and structures.
     */
    namespace Archive {

        public delegate bool IsSupportedCallback();
        public delegate void* NewArchiveCallback(string path); //
        public delegate void* OpenArchiveCallback(string path); //
        public delegate bool ExtractArchiveCallback(string path, string dest); //

        /**
         * Mapping of each format's functions.<br />
         * <br />
         * This is actually a class-based enum, because Vala enums suck.
         */
        public class Format : GLib.Object {

            public static Format RAR = new Format(3, "RAR", _Internal_.rar_is_supported,
                                                            _Internal_.rar_new,
                                                            _Internal_.rar_open,
                                                            _Internal_.rar_extract);
            public static Format S7Z = new Format(0, "S7Z", _Internal_.s7z_is_supported,
                                                            _Internal_.s7z_new,
                                                            _Internal_.s7z_open,
                                                            _Internal_.s7z_extract);
            public static Format TAR = new Format(2, "TAR", _Internal_.tar_is_supported,
                                                            _Internal_.tar_new,
                                                            _Internal_.tar_open,
                                                            _Internal_.tar_extract);
            public static Format ZIP = new Format(1, "ZIP", _Internal_.zip_is_supported,
                                                            _Internal_.zip_new,
                                                            _Internal_.zip_open,
                                                            _Internal_.zip_extract);

            public static Format[] VALUES = new Format[] {RAR, S7Z, TAR, ZIP};

            /**
             * Vala needs to call `class_init` on this object, so create a dummy object.
             *
             * Also, fill the format list.
             */
            internal static void init() {
                new Archive.Format(-1, "no-op", ()           => { return false; },
                                                (path)       => { return null;  },
                                                (path)       => { return null;  },
                                                (path, dest) => { return false; });

#if UC_DEBUG_ENABLED
                foreach (Format format in VALUES) {
                    stdout.printf("Archive Format #%d (%s): %s \n", format.index, format.name, (format.is_supported() ? "" : "not ") + "supported");
                }
#endif // UC_DEBUG_ENABLED
            }

            public static Format? determine_from_file(File file) {
                stderr.printf("TODO determine_from_file()");
                return null;
            }

            /**
             * The position of this value in the `_uc_archive` enum
             */
            private int                    index        { public get;  private set; }
            public  string                 name         { public get;  private set; }
            private IsSupportedCallback    supported_cb { private get; private set; }
            private NewArchiveCallback     new_cb       { private get; private set; }
            private OpenArchiveCallback    open_cb      { private get; private set; }
            private ExtractArchiveCallback extract_cb   { private get; private set; }

            [CCode (construct_function = null)]
            private Format(int index, string name, IsSupportedCallback supported_cb,
                                                   NewArchiveCallback new_cb,
                                                   OpenArchiveCallback open_cb,
                                                   ExtractArchiveCallback extract_cb) {
                this.index = index;
                this.name = name;
                this.supported_cb = supported_cb;
                this.new_cb       = new_cb;
                this.open_cb      = open_cb;
                this.extract_cb   = extract_cb;
            }

            public bool is_supported() {
                return supported_cb();
            }
        }
    }

    /**
     * Internal use only. Always use functions from `UltimateCompressor.Archive` namespace.
     */
    namespace _Internal_ {

        // --- rar
        [CCode (cname = "uc_arc_rar_is_supported")]
	    private extern bool rar_is_supported();
	    [CCode (cname = "uc_arc_rar_new")]
        private extern void* rar_new(string path);
        [CCode (cname = "uc_arc_rar_open")]
        private extern void* rar_open(string path);
        [CCode (cname = "uc_arc_rar_extract")]
        private extern bool rar_extract(string path, string dest);

	    // --- 7z
        [CCode (cname = "uc_arc_s7z_is_supported")]
	    private extern bool s7z_is_supported();
	    [CCode (cname = "uc_arc_s7z_new")]
        private extern void* s7z_new(string path);
        [CCode (cname = "uc_arc_s7z_open")]
        private extern void* s7z_open(string path);
        [CCode (cname = "uc_arc_s7z_extract")]
        private extern bool s7z_extract(string path, string dest);

	    // --- tar
        [CCode (cname = "uc_arc_tar_is_supported")]
	    private extern bool tar_is_supported();
	    [CCode (cname = "uc_arc_tar_new")]
        private extern void* tar_new(string path);
        [CCode (cname = "uc_arc_tar_open")]
        private extern void* tar_open(string path);
        [CCode (cname = "uc_arc_tar_extract")]
        private extern bool tar_extract(string path, string dest);

	    // --- zip
        [CCode (cname = "uc_arc_zip_is_supported")]
	    private extern bool zip_is_supported();
	    [CCode (cname = "uc_arc_zip_new")]
        private extern void* zip_new(string path);
        [CCode (cname = "uc_arc_zip_open")]
        private extern void* zip_open(string path);
        [CCode (cname = "uc_arc_zip_extract")]
        private extern bool zip_extract(string path, string dest);

    }

}