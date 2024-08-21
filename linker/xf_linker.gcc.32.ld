/**
 * @file
 * @brief Linker command/script file
 *
 * Linker script for the POSIX (native) platform
 */

SECTIONS
{
  xf_auto_init : {
  . = ALIGN(4);
  __xf_init_start = .;
  KEEP(*(SORT(.xf_auto_init*)))
  __xf_init_end = .;
  . = ALIGN(4);
  }
} INSERT AFTER .text;

/*
 * Note that the INSERT command actually changes the meaning of the -T command
 * line switch: The script will now augment the default SECTIONS instead of
 * replacing it.
 */
