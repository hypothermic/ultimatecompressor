using GLib;

/*
 * Vala doesn't have macro's so we have to define each individual function for each archive format....
 *
 * Fuck you Vala!
 */

namespace UltimateCompressor.Archive {

    public delegate bool Callback();

    public class Format : GLib.Object {

        public static Format RAR = new Format(3, UC.Arc.rar_is_supported);
        public static Format S7Z = new Format(0, UC.Arc.s7z_is_supported);
        public static Format TAR = new Format(2, UC.Arc.tar_is_supported);
        public static Format ZIP = new Format(1, UC.Arc.zip_is_supported);

        /**
         * The position of this value in the `_uc_archive` enum
         */
        private int index { get; set; }
        private Callback supported_cb { get; set; }

        [CCode (construct_function = null)]
        private Format(int index, Callback supported_cb) {
            this.index = index;
            this.supported_cb = supported_cb;
        }
    }

}

/**
 * Internal use only. Always use functions from `UltimateCompressor.Archive` namespace.
 */
namespace UC.Arc {

	extern bool rar_is_supported();
	extern bool s7z_is_supported();
	extern bool tar_is_supported();
	extern bool zip_is_supported();

}