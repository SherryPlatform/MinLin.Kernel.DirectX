# MinLin.Kernel.DirectX

Out-of-tree Linux Kernel Module for dxgkrnl from Windows Subsystem for Linux 2
(WSL 2) but used in MinLin.

## Version

The dxgkrnl kernel module in this project current use commit 
https://github.com/microsoft/WSL2-Linux-Kernel/tree/e8c50f197b62b147dbc3e3ee083dd1fbb66eaeaf.

In order to show the detailed commit history of the original dxgkrnl kernel to
help people know the modifications, this project format the patch from the
original Linux Kernel source code repository tree, do some modifications to
redirect the folders, remove the unused files for out-of-tree Linux kernel
modules, and finally apply patches to this project repository directly. For
more information about the modified patches, please read the history for
[Patches](Patches) folder.

## License

MinLin.Kernel.DirectX is distributed under the same license from Linux Kernel
because this is a out-of-tree Linux kernel module. For more information, have a
look at https://github.com/torvalds/linux/blob/master/COPYING.
