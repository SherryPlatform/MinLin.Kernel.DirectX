/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */

/*
 * Copyright (c) 2019, Microsoft Corporation.
 *
 * Author:
 *   Iouri Tarassov <iourit@linux.microsoft.com>
 *
 * Dxgkrnl Graphics Driver
 * User mode WDDM interface definitions
 *
 */

#ifndef _D3DKMTHK_H
#define _D3DKMTHK_H

/*
 * This structure matches the definition of D3DKMTHANDLE in Windows.
 * The handle is opaque in user mode. It is used by user mode applications to
 * represent kernel mode objects, created by dxgkrnl.
 */
struct d3dkmthandle {
	union {
		struct {
			__u32 instance	:  6;
			__u32 index	: 24;
			__u32 unique	: 2;
		};
		__u32 v;
	};
};

/*
 * VM bus messages return Windows' NTSTATUS, which is integer and only negative
 * value indicates a failure. A positive number is a success and needs to be
 * returned to user mode as the IOCTL return code. Negative status codes are
 * converted to Linux error codes.
 */
struct ntstatus {
	union {
		struct {
			int code	: 16;
			int facility	: 13;
			int customer	: 1;
			int severity	: 2;
		};
		int v;
	};
};

/*
 * Matches the Windows LUID definition.
 * LUID is a locally unique identifier (similar to GUID, but not global),
 * which is guaranteed to be unique intil the computer is rebooted.
 */
struct winluid {
	__u32 a;
	__u32 b;
};

#define D3DKMT_CREATEALLOCATION_MAX		1024
#define D3DKMT_ADAPTERS_MAX			64

struct d3dkmt_adapterinfo {
	struct d3dkmthandle		adapter_handle;
	struct winluid			adapter_luid;
	__u32				num_sources;
	__u32				present_move_regions_preferred;
};

struct d3dkmt_enumadapters2 {
	__u32				num_adapters;
	__u32				reserved;
#ifdef __KERNEL__
	struct d3dkmt_adapterinfo	*adapters;
#else
	__u64				*adapters;
#endif
};

struct d3dkmt_closeadapter {
	struct d3dkmthandle		adapter_handle;
};

struct d3dkmt_openadapterfromluid {
	struct winluid			adapter_luid;
	struct d3dkmthandle		adapter_handle;
};

struct d3dddi_allocationlist {
	struct d3dkmthandle		allocation;
	union {
		struct {
			__u32		write_operation		:1;
			__u32		do_not_retire_instance	:1;
			__u32		offer_priority		:3;
			__u32		reserved		:27;
		};
		__u32			value;
	};
};

struct d3dddi_patchlocationlist {
	__u32				allocation_index;
	union {
		struct {
			__u32		slot_id:24;
			__u32		reserved:8;
		};
		__u32			value;
	};
	__u32				driver_id;
	__u32				allocation_offset;
	__u32				patch_offset;
	__u32				split_offset;
};

struct d3dkmt_createdeviceflags {
	__u32				legacy_mode:1;
	__u32				request_vSync:1;
	__u32				disable_gpu_timeout:1;
	__u32				gdi_device:1;
	__u32				reserved:28;
};

struct d3dkmt_createdevice {
	struct d3dkmthandle		adapter;
	__u32				reserved3;
	struct d3dkmt_createdeviceflags	flags;
	struct d3dkmthandle		device;
#ifdef __KERNEL__
	void				*command_buffer;
#else
	__u64				command_buffer;
#endif
	__u32				command_buffer_size;
	__u32				reserved;
#ifdef __KERNEL__
	struct d3dddi_allocationlist	*allocation_list;
#else
	__u64				allocation_list;
#endif
	__u32				allocation_list_size;
	__u32				reserved1;
#ifdef __KERNEL__
	struct d3dddi_patchlocationlist	*patch_location_list;
#else
	__u64				patch_location_list;
#endif
	__u32				patch_location_list_size;
	__u32				reserved2;
};

struct d3dkmt_destroydevice {
	struct d3dkmthandle		device;
};

enum d3dkmt_clienthint {
	_D3DKMT_CLIENTHNT_UNKNOWN	= 0,
	_D3DKMT_CLIENTHINT_OPENGL	= 1,
	_D3DKMT_CLIENTHINT_CDD		= 2,
	_D3DKMT_CLIENTHINT_DX7		= 7,
	_D3DKMT_CLIENTHINT_DX8		= 8,
	_D3DKMT_CLIENTHINT_DX9		= 9,
	_D3DKMT_CLIENTHINT_DX10		= 10,
};

struct d3dddi_createcontextflags {
	union {
		struct {
			__u32		null_rendering:1;
			__u32		initial_data:1;
			__u32		disable_gpu_timeout:1;
			__u32		synchronization_only:1;
			__u32		hw_queue_supported:1;
			__u32		reserved:27;
		};
		__u32			value;
	};
};

struct d3dkmt_destroycontext {
	struct d3dkmthandle		context;
};

struct d3dkmt_createcontextvirtual {
	struct d3dkmthandle		device;
	__u32				node_ordinal;
	__u32				engine_affinity;
	struct d3dddi_createcontextflags flags;
#ifdef __KERNEL__
	void				*priv_drv_data;
#else
	__u64				priv_drv_data;
#endif
	__u32				priv_drv_data_size;
	enum d3dkmt_clienthint		client_hint;
	struct d3dkmthandle		context;
};

enum d3dkmdt_gdisurfacetype {
	_D3DKMDT_GDISURFACE_INVALID				= 0,
	_D3DKMDT_GDISURFACE_TEXTURE				= 1,
	_D3DKMDT_GDISURFACE_STAGING_CPUVISIBLE			= 2,
	_D3DKMDT_GDISURFACE_STAGING				= 3,
	_D3DKMDT_GDISURFACE_LOOKUPTABLE				= 4,
	_D3DKMDT_GDISURFACE_EXISTINGSYSMEM			= 5,
	_D3DKMDT_GDISURFACE_TEXTURE_CPUVISIBLE			= 6,
	_D3DKMDT_GDISURFACE_TEXTURE_CROSSADAPTER		= 7,
	_D3DKMDT_GDISURFACE_TEXTURE_CPUVISIBLE_CROSSADAPTER	= 8,
};

struct d3dddi_rational {
	__u32	numerator;
	__u32	denominator;
};

enum d3dddiformat {
	_D3DDDIFMT_UNKNOWN = 0,
};

struct d3dkmdt_gdisurfacedata {
	__u32				width;
	__u32				height;
	__u32				format;
	enum d3dkmdt_gdisurfacetype	type;
	__u32				flags;
	__u32				pitch;
};

struct d3dkmdt_stagingsurfacedata {
	__u32	width;
	__u32	height;
	__u32	pitch;
};

struct d3dkmdt_sharedprimarysurfacedata {
	__u32			width;
	__u32			height;
	enum d3dddiformat	format;
	struct d3dddi_rational	refresh_rate;
	__u32			vidpn_source_id;
};

struct d3dkmdt_shadowsurfacedata {
	__u32			width;
	__u32			height;
	enum d3dddiformat	format;
	__u32			pitch;
};

enum d3dkmdt_standardallocationtype {
	_D3DKMDT_STANDARDALLOCATION_SHAREDPRIMARYSURFACE	= 1,
	_D3DKMDT_STANDARDALLOCATION_SHADOWSURFACE		= 2,
	_D3DKMDT_STANDARDALLOCATION_STAGINGSURFACE		= 3,
	_D3DKMDT_STANDARDALLOCATION_GDISURFACE			= 4,
};

enum d3dkmt_standardallocationtype {
	_D3DKMT_STANDARDALLOCATIONTYPE_EXISTINGHEAP	= 1,
	_D3DKMT_STANDARDALLOCATIONTYPE_CROSSADAPTER	= 2,
};

struct d3dkmt_standardallocation_existingheap {
	__u64	size;
};

struct d3dkmt_createstandardallocationflags {
	union {
		struct {
			__u32		reserved:32;
		};
		__u32			value;
	};
};

struct d3dkmt_createstandardallocation {
	enum d3dkmt_standardallocationtype		type;
	__u32						reserved;
	struct d3dkmt_standardallocation_existingheap	existing_heap_data;
	struct d3dkmt_createstandardallocationflags	flags;
	__u32						reserved1;
};

struct d3dddi_allocationinfo2 {
	struct d3dkmthandle	allocation;
#ifdef __KERNEL__
	const void		*sysmem;
#else
	__u64			sysmem;
#endif
#ifdef __KERNEL__
	void			*priv_drv_data;
#else
	__u64			priv_drv_data;
#endif
	__u32			priv_drv_data_size;
	__u32			vidpn_source_id;
	union {
		struct {
			__u32	primary:1;
			__u32	stereo:1;
			__u32	override_priority:1;
			__u32	reserved:29;
		};
		__u32		value;
	} flags;
	__u64			gpu_virtual_address;
	union {
		__u32		priority;
		__u64		unused;
	};
	__u64			reserved[5];
};

struct d3dkmt_createallocationflags {
	union {
		struct {
			__u32		create_resource:1;
			__u32		create_shared:1;
			__u32		non_secure:1;
			__u32		create_protected:1;
			__u32		restrict_shared_access:1;
			__u32		existing_sysmem:1;
			__u32		nt_security_sharing:1;
			__u32		read_only:1;
			__u32		create_write_combined:1;
			__u32		create_cached:1;
			__u32		swap_chain_back_buffer:1;
			__u32		cross_adapter:1;
			__u32		open_cross_adapter:1;
			__u32		partial_shared_creation:1;
			__u32		zeroed:1;
			__u32		write_watch:1;
			__u32		standard_allocation:1;
			__u32		existing_section:1;
			__u32		reserved:14;
		};
		__u32			value;
	};
};

struct d3dkmt_createallocation {
	struct d3dkmthandle		device;
	struct d3dkmthandle		resource;
	struct d3dkmthandle		global_share;
	__u32				reserved;
#ifdef __KERNEL__
	const void			*private_runtime_data;
#else
	__u64				private_runtime_data;
#endif
	__u32				private_runtime_data_size;
	__u32				reserved1;
	union {
#ifdef __KERNEL__
		struct d3dkmt_createstandardallocation *standard_allocation;
		const void *priv_drv_data;
#else
		__u64	standard_allocation;
		__u64	priv_drv_data;
#endif
	};
	__u32				priv_drv_data_size;
	__u32				alloc_count;
#ifdef __KERNEL__
	struct d3dddi_allocationinfo2	*allocation_info;
#else
	__u64				allocation_info;
#endif
	struct d3dkmt_createallocationflags flags;
	__u32				reserved2;
	__u64				private_runtime_resource_handle;
};

struct d3dddicb_destroyallocation2flags {
	union {
		struct {
			__u32		assume_not_in_use:1;
			__u32		synchronous_destroy:1;
			__u32		reserved:29;
			__u32		system_use_only:1;
		};
		__u32			value;
	};
};

struct d3dkmt_destroyallocation2 {
	struct d3dkmthandle		device;
	struct d3dkmthandle		resource;
#ifdef __KERNEL__
	const struct d3dkmthandle	*allocations;
#else
	__u64				allocations;
#endif
	__u32				alloc_count;
	struct d3dddicb_destroyallocation2flags flags;
};

struct d3dkmt_adaptertype {
	union {
		struct {
			__u32		render_supported:1;
			__u32		display_supported:1;
			__u32		software_device:1;
			__u32		post_device:1;
			__u32		hybrid_discrete:1;
			__u32		hybrid_integrated:1;
			__u32		indirect_display_device:1;
			__u32		paravirtualized:1;
			__u32		acg_supported:1;
			__u32		support_set_timings_from_vidpn:1;
			__u32		detachable:1;
			__u32		compute_only:1;
			__u32		prototype:1;
			__u32		reserved:19;
		};
		__u32			value;
	};
};

enum kmtqueryadapterinfotype {
	_KMTQAITYPE_UMDRIVERPRIVATE	= 0,
	_KMTQAITYPE_ADAPTERTYPE		= 15,
	_KMTQAITYPE_ADAPTERTYPE_RENDER	= 57
};

struct d3dkmt_queryadapterinfo {
	struct d3dkmthandle		adapter;
	enum kmtqueryadapterinfotype	type;
#ifdef __KERNEL__
	void				*private_data;
#else
	__u64				private_data;
#endif
	__u32				private_data_size;
};

enum d3dkmt_deviceexecution_state {
	_D3DKMT_DEVICEEXECUTION_ACTIVE			= 1,
	_D3DKMT_DEVICEEXECUTION_RESET			= 2,
	_D3DKMT_DEVICEEXECUTION_HUNG			= 3,
	_D3DKMT_DEVICEEXECUTION_STOPPED			= 4,
	_D3DKMT_DEVICEEXECUTION_ERROR_OUTOFMEMORY	= 5,
	_D3DKMT_DEVICEEXECUTION_ERROR_DMAFAULT		= 6,
	_D3DKMT_DEVICEEXECUTION_ERROR_DMAPAGEFAULT	= 7,
};

union d3dkmt_enumadapters_filter {
	struct {
		__u64	include_compute_only:1;
		__u64	include_display_only:1;
		__u64	reserved:62;
	};
	__u64		value;
};

struct d3dkmt_enumadapters3 {
	union d3dkmt_enumadapters_filter	filter;
	__u32					adapter_count;
	__u32					reserved;
#ifdef __KERNEL__
	struct d3dkmt_adapterinfo		*adapters;
#else
	__u64					adapters;
#endif
};

/*
 * Dxgkrnl Graphics Port Driver ioctl definitions
 *
 */

#define LX_DXOPENADAPTERFROMLUID	\
	_IOWR(0x47, 0x01, struct d3dkmt_openadapterfromluid)
#define LX_DXCREATEDEVICE		\
	_IOWR(0x47, 0x02, struct d3dkmt_createdevice)
#define LX_DXCREATECONTEXTVIRTUAL	\
	_IOWR(0x47, 0x04, struct d3dkmt_createcontextvirtual)
#define LX_DXDESTROYCONTEXT		\
	_IOWR(0x47, 0x05, struct d3dkmt_destroycontext)
#define LX_DXCREATEALLOCATION		\
	_IOWR(0x47, 0x06, struct d3dkmt_createallocation)
#define LX_DXQUERYADAPTERINFO		\
	_IOWR(0x47, 0x09, struct d3dkmt_queryadapterinfo)
#define LX_DXDESTROYALLOCATION2		\
	_IOWR(0x47, 0x13, struct d3dkmt_destroyallocation2)
#define LX_DXENUMADAPTERS2		\
	_IOWR(0x47, 0x14, struct d3dkmt_enumadapters2)
#define LX_DXCLOSEADAPTER		\
	_IOWR(0x47, 0x15, struct d3dkmt_closeadapter)
#define LX_DXDESTROYDEVICE		\
	_IOWR(0x47, 0x19, struct d3dkmt_destroydevice)
#define LX_DXENUMADAPTERS3		\
	_IOWR(0x47, 0x3e, struct d3dkmt_enumadapters3)

#endif /* _D3DKMTHK_H */
