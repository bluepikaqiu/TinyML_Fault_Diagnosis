MEMORY
{
  UNPLACED_SECTIONS (wx) : ORIGIN = 0x100000000, LENGTH = 0
  FLASH1 (rx) : ORIGIN = 0x00000000, LENGTH = 0x00100000
  RAM1 (wx) : ORIGIN = 0x20000000, LENGTH = 0x00040000
}

SECTIONS
{
  __FLASH1_segment_start__ = 0x00000000;
  __FLASH1_segment_end__ = 0x00100000;
  __FLASH1_segment_size__ = 0x00100000;
  __RAM1_segment_start__ = 0x20000000;
  __RAM1_segment_end__ = 0x20040000;
  __RAM1_segment_size__ = 0x00040000;

  __HEAPSIZE__ = 16384;
  __SEGGER_RTL_vfprintf = __SEGGER_RTL_vfprintf_short_float_long;
  __SEGGER_RTL_vfscanf = __SEGGER_RTL_vfscanf_long;
  __STACKSIZE_PROCESS__ = 0;
  __STACKSIZE__ = 16384;
  __dso_handle = 0;

}

