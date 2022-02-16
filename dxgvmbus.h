/* SPDX-License-Identifier: GPL-2.0 */

/*
 * Copyright (c) 2022, Microsoft Corporation.
 *
 * Author:
 *   Iouri Tarassov <iourit@linux.microsoft.com>
 *
 * Dxgkrnl Graphics Driver
 * VM bus interface with the host definitions
 *
 */

#ifndef _DXGVMBUS_H
#define _DXGVMBUS_H

struct dxgprocess;
struct dxgadapter;

#define DXG_MAX_VM_BUS_PACKET_SIZE	(1024 * 128)
#define DXG_VM_PROCESS_NAME_LENGTH	260

enum dxgkvmb_commandchanneltype {
	DXGKVMB_VGPU_TO_HOST,
	DXGKVMB_VM_TO_HOST,
	DXGKVMB_HOST_TO_VM
};

/*
 *
 * Commands, sent to the host via the guest global VM bus channel
 * DXG_GUEST_GLOBAL_VMBUS
 *
 */

enum dxgkvmb_commandtype_global {
	DXGK_VMBCOMMAND_VM_TO_HOST_FIRST	= 1000,
	DXGK_VMBCOMMAND_CREATEPROCESS	= DXGK_VMBCOMMAND_VM_TO_HOST_FIRST,
	DXGK_VMBCOMMAND_DESTROYPROCESS		= 1001,
	DXGK_VMBCOMMAND_OPENSYNCOBJECT		= 1002,
	DXGK_VMBCOMMAND_DESTROYSYNCOBJECT	= 1003,
	DXGK_VMBCOMMAND_CREATENTSHAREDOBJECT	= 1004,
	DXGK_VMBCOMMAND_DESTROYNTSHAREDOBJECT	= 1005,
	DXGK_VMBCOMMAND_SIGNALFENCE		= 1006,
	DXGK_VMBCOMMAND_NOTIFYPROCESSFREEZE	= 1007,
	DXGK_VMBCOMMAND_NOTIFYPROCESSTHAW	= 1008,
	DXGK_VMBCOMMAND_QUERYETWSESSION		= 1009,
	DXGK_VMBCOMMAND_SETIOSPACEREGION	= 1010,
	DXGK_VMBCOMMAND_COMPLETETRANSACTION	= 1011,
	DXGK_VMBCOMMAND_SHAREOBJECTWITHHOST	= 1021,
	DXGK_VMBCOMMAND_INVALID_VM_TO_HOST
};

/*
 *
 * Commands, sent to the host via the per adapter VM bus channel
 * DXG_GUEST_VGPU_VMBUS
 *
 */

enum dxgkvmb_commandtype {
	DXGK_VMBCOMMAND_CREATEDEVICE		= 0,
	DXGK_VMBCOMMAND_DESTROYDEVICE		= 1,
	DXGK_VMBCOMMAND_QUERYADAPTERINFO	= 2,
	DXGK_VMBCOMMAND_DDIQUERYADAPTERINFO	= 3,
	DXGK_VMBCOMMAND_CREATEALLOCATION	= 4,
	DXGK_VMBCOMMAND_DESTROYALLOCATION	= 5,
	DXGK_VMBCOMMAND_CREATECONTEXTVIRTUAL	= 6,
	DXGK_VMBCOMMAND_DESTROYCONTEXT		= 7,
	DXGK_VMBCOMMAND_CREATESYNCOBJECT	= 8,
	DXGK_VMBCOMMAND_CREATEPAGINGQUEUE	= 9,
	DXGK_VMBCOMMAND_DESTROYPAGINGQUEUE	= 10,
	DXGK_VMBCOMMAND_MAKERESIDENT		= 11,
	DXGK_VMBCOMMAND_EVICT			= 12,
	DXGK_VMBCOMMAND_ESCAPE			= 13,
	DXGK_VMBCOMMAND_OPENADAPTER		= 14,
	DXGK_VMBCOMMAND_CLOSEADAPTER		= 15,
	DXGK_VMBCOMMAND_FREEGPUVIRTUALADDRESS	= 16,
	DXGK_VMBCOMMAND_MAPGPUVIRTUALADDRESS	= 17,
	DXGK_VMBCOMMAND_RESERVEGPUVIRTUALADDRESS = 18,
	DXGK_VMBCOMMAND_UPDATEGPUVIRTUALADDRESS	= 19,
	DXGK_VMBCOMMAND_SUBMITCOMMAND		= 20,
	dxgk_vmbcommand_queryvideomemoryinfo	= 21,
	DXGK_VMBCOMMAND_WAITFORSYNCOBJECTFROMCPU = 22,
	DXGK_VMBCOMMAND_LOCK2			= 23,
	DXGK_VMBCOMMAND_UNLOCK2			= 24,
	DXGK_VMBCOMMAND_WAITFORSYNCOBJECTFROMGPU = 25,
	DXGK_VMBCOMMAND_SIGNALSYNCOBJECT	= 26,
	DXGK_VMBCOMMAND_SIGNALFENCENTSHAREDBYREF = 27,
	DXGK_VMBCOMMAND_GETDEVICESTATE		= 28,
	DXGK_VMBCOMMAND_MARKDEVICEASERROR	= 29,
	DXGK_VMBCOMMAND_ADAPTERSTOP		= 30,
	DXGK_VMBCOMMAND_SETQUEUEDLIMIT		= 31,
	DXGK_VMBCOMMAND_OPENRESOURCE		= 32,
	DXGK_VMBCOMMAND_SETCONTEXTSCHEDULINGPRIORITY = 33,
	DXGK_VMBCOMMAND_PRESENTHISTORYTOKEN	= 34,
	DXGK_VMBCOMMAND_SETREDIRECTEDFLIPFENCEVALUE = 35,
	DXGK_VMBCOMMAND_GETINTERNALADAPTERINFO	= 36,
	DXGK_VMBCOMMAND_FLUSHHEAPTRANSITIONS	= 37,
	DXGK_VMBCOMMAND_BLT			= 38,
	DXGK_VMBCOMMAND_DDIGETSTANDARDALLOCATIONDRIVERDATA = 39,
	DXGK_VMBCOMMAND_CDDGDICOMMAND		= 40,
	DXGK_VMBCOMMAND_QUERYALLOCATIONRESIDENCY = 41,
	DXGK_VMBCOMMAND_FLUSHDEVICE		= 42,
	DXGK_VMBCOMMAND_FLUSHADAPTER		= 43,
	DXGK_VMBCOMMAND_DDIGETNODEMETADATA	= 44,
	DXGK_VMBCOMMAND_SETEXISTINGSYSMEMSTORE	= 45,
	DXGK_VMBCOMMAND_ISSYNCOBJECTSIGNALED	= 46,
	DXGK_VMBCOMMAND_CDDSYNCGPUACCESS	= 47,
	DXGK_VMBCOMMAND_QUERYSTATISTICS		= 48,
	DXGK_VMBCOMMAND_CHANGEVIDEOMEMORYRESERVATION = 49,
	DXGK_VMBCOMMAND_CREATEHWQUEUE		= 50,
	DXGK_VMBCOMMAND_DESTROYHWQUEUE		= 51,
	DXGK_VMBCOMMAND_SUBMITCOMMANDTOHWQUEUE	= 52,
	DXGK_VMBCOMMAND_GETDRIVERSTOREFILE	= 53,
	DXGK_VMBCOMMAND_READDRIVERSTOREFILE	= 54,
	DXGK_VMBCOMMAND_GETNEXTHARDLINK		= 55,
	DXGK_VMBCOMMAND_UPDATEALLOCATIONPROPERTY = 56,
	DXGK_VMBCOMMAND_OFFERALLOCATIONS	= 57,
	DXGK_VMBCOMMAND_RECLAIMALLOCATIONS	= 58,
	DXGK_VMBCOMMAND_SETALLOCATIONPRIORITY	= 59,
	DXGK_VMBCOMMAND_GETALLOCATIONPRIORITY	= 60,
	DXGK_VMBCOMMAND_GETCONTEXTSCHEDULINGPRIORITY = 61,
	DXGK_VMBCOMMAND_QUERYCLOCKCALIBRATION	= 62,
	DXGK_VMBCOMMAND_QUERYRESOURCEINFO	= 64,
	DXGK_VMBCOMMAND_LOGEVENT		= 65,
	DXGK_VMBCOMMAND_SETEXISTINGSYSMEMPAGES	= 66,
	DXGK_VMBCOMMAND_INVALID
};

/*
 * Commands, sent by the host to the VM
 */
enum dxgkvmb_commandtype_host_to_vm {
	DXGK_VMBCOMMAND_SIGNALGUESTEVENT,
	DXGK_VMBCOMMAND_PROPAGATEPRESENTHISTORYTOKEN,
	DXGK_VMBCOMMAND_SETGUESTDATA,
	DXGK_VMBCOMMAND_SIGNALGUESTEVENTPASSIVE,
	DXGK_VMBCOMMAND_SENDWNFNOTIFICATION,
	DXGK_VMBCOMMAND_INVALID_HOST_TO_VM
};

struct dxgkvmb_command_vm_to_host {
	u64				command_id;
	struct d3dkmthandle		process;
	enum dxgkvmb_commandchanneltype	channel_type;
	enum dxgkvmb_commandtype_global	command_type;
};

struct dxgkvmb_command_vgpu_to_host {
	u64				command_id;
	struct d3dkmthandle		process;
	u32				channel_type	: 8;
	u32				async_msg	: 1;
	u32				reserved	: 23;
	enum dxgkvmb_commandtype	command_type;
};

struct dxgkvmb_command_host_to_vm {
	u64					command_id;
	struct d3dkmthandle			process;
	u32					channel_type	: 8;
	u32					async_msg	: 1;
	u32					reserved	: 23;
	enum dxgkvmb_commandtype_host_to_vm	command_type;
};

/* Returns ntstatus */
struct dxgkvmb_command_setiospaceregion {
	struct dxgkvmb_command_vm_to_host hdr;
	u64				start;
	u64				length;
	u32				shared_page_gpadl;
};

struct dxgkvmb_command_createprocess {
	struct dxgkvmb_command_vm_to_host hdr;
	void			*process;
	u64			process_id;
	u16			process_name[DXG_VM_PROCESS_NAME_LENGTH + 1];
	u8			csrss_process:1;
	u8			dwm_process:1;
	u8			wow64_process:1;
	u8			linux_process:1;
};

struct dxgkvmb_command_createprocess_return {
	struct d3dkmthandle	hprocess;
};

// The command returns ntstatus
struct dxgkvmb_command_destroyprocess {
	struct dxgkvmb_command_vm_to_host hdr;
};

struct dxgkvmb_command_openadapter {
	struct dxgkvmb_command_vgpu_to_host hdr;
	u32				vmbus_interface_version;
	u32				vmbus_last_compatible_interface_version;
	struct winluid			guest_adapter_luid;
};

struct dxgkvmb_command_openadapter_return {
	struct d3dkmthandle		host_adapter_handle;
	struct ntstatus			status;
	u32				vmbus_interface_version;
	u32				vmbus_last_compatible_interface_version;
};

struct dxgkvmb_command_closeadapter {
	struct dxgkvmb_command_vgpu_to_host hdr;
	struct d3dkmthandle		host_handle;
};

struct dxgkvmb_command_getinternaladapterinfo {
	struct dxgkvmb_command_vgpu_to_host hdr;
};

struct dxgkvmb_command_getinternaladapterinfo_return {
	struct dxgk_device_types	device_types;
	u32				driver_store_copy_mode;
	u32				driver_ddi_version;
	u32				secure_virtual_machine	: 1;
	u32				virtual_machine_reset	: 1;
	u32				is_vail_supported	: 1;
	u32				hw_sch_enabled		: 1;
	u32				hw_sch_capable		: 1;
	u32				va_backed_vm		: 1;
	u32				async_msg_enabled	: 1;
	u32				hw_support_state	: 2;
	u32				reserved		: 23;
	struct winluid			host_adapter_luid;
	u16				device_description[80];
	u16				device_instance_id[WIN_MAX_PATH];
	struct winluid			host_vgpu_luid;
};

struct dxgkvmb_command_queryadapterinfo {
	struct dxgkvmb_command_vgpu_to_host hdr;
	enum kmtqueryadapterinfotype	query_type;
	u32				private_data_size;
	u8				private_data[1];
};

struct dxgkvmb_command_queryadapterinfo_return {
	struct ntstatus			status;
	u8				private_data[1];
};

#endif /* _DXGVMBUS_H */
