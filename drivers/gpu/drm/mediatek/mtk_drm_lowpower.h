/*
 * Copyright (c) 2019 MediaTek Inc.
 * Copyright (C) 2021 XiaoMi, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef _MTK_DRM_LOWPOWER_H_
#define _MTK_DRM_LOWPOWER_H_

#include <linux/workqueue.h>
#include <drm/drm_crtc.h>

struct mtk_drm_idlemgr_context {
	unsigned long long idle_check_interval;
	unsigned long long idlemgr_last_kick_time;
	unsigned int enterulps;
	int session_mode_before_enter_idle;
	int is_idle;
	int is_idle_fps;
	bool dfps_en;
	int cur_lp_cust_mode;
};

struct mtk_drm_idlemgr {
	struct task_struct *idlemgr_task;
	wait_queue_head_t idlemgr_wq;
	atomic_t idlemgr_task_active;
	struct mtk_drm_idlemgr_context *idlemgr_ctx;
	struct delayed_work touch_up_event_delay_work;
};

void mtk_drm_idlemgr_kick(const char *source, struct drm_crtc *crtc,
			  int need_lock);
bool mtk_drm_is_idle(struct drm_crtc *crtc);
#ifdef CONFIG_DRM_DFPS
bool mtk_drm_is_idle_fps(struct drm_crtc *crtc);
bool mtk_drm_enable_idle_fps(struct drm_crtc *crtc);
bool mtk_drm_idlemgr_enable_dfps(struct drm_crtc *crtc, bool en);
#endif
int mtk_drm_idlemgr_init(struct drm_crtc *crtc, int index);
unsigned int mtk_drm_set_idlemgr(struct drm_crtc *crtc, unsigned int flag,
				 bool need_lock);
unsigned long long
mtk_drm_set_idle_check_interval(struct drm_crtc *crtc,
				unsigned long long new_interval);
unsigned long long
mtk_drm_get_idle_check_interval(struct drm_crtc *crtc);

#endif
