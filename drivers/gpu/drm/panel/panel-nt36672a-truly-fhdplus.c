// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2020 FIXME
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2013, The Linux Foundation. All rights reserved. (FIXME)

#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/regulator/consumer.h>

#include <video/mipi_display.h>

#include <drm/drm_mipi_dsi.h>
#include <drm/drm_modes.h>
#include <drm/drm_panel.h>

struct nt36672a_truly_fhdplus {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	struct regulator_bulk_data supplies[4];
	struct gpio_desc *reset_gpio;
	bool prepared;
};

static inline
struct nt36672a_truly_fhdplus *to_nt36672a_truly_fhdplus(struct drm_panel *panel)
{
	return container_of(panel, struct nt36672a_truly_fhdplus, panel);
}

#define dsi_dcs_write_seq(dsi, seq...) do {				\
		static const u8 d[] = { seq };				\
		int ret;						\
		ret = mipi_dsi_dcs_write_buffer(dsi, d, ARRAY_SIZE(d));	\
		if (ret < 0)						\
			return ret;					\
	} while (0)

static void nt36672a_truly_fhdplus_reset(struct nt36672a_truly_fhdplus *ctx)
{
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(10000, 11000);
}

static int nt36672a_truly_fhdplus_on(struct nt36672a_truly_fhdplus *ctx)
{
	struct mipi_dsi_device *dsi = ctx->dsi;
	struct device *dev = &dsi->dev;
	int ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	dsi_dcs_write_seq(dsi, 0xff, 0x10);
	dsi_dcs_write_seq(dsi, 0xfb, 0x01);
	dsi_dcs_write_seq(dsi, 0xff, 0x20);
	dsi_dcs_write_seq(dsi, 0xfb, 0x01);
	dsi_dcs_write_seq(dsi, MIPI_DCS_GET_SIGNAL_MODE, 0xb0);
	dsi_dcs_write_seq(dsi, MIPI_DCS_GET_DIAGNOSTIC_RESULT, 0xae);
	dsi_dcs_write_seq(dsi, 0x62, 0x93);
	dsi_dcs_write_seq(dsi, 0x6d, 0x44);
	dsi_dcs_write_seq(dsi, 0x78, 0x01);
	dsi_dcs_write_seq(dsi, 0x89, 0x12);
	dsi_dcs_write_seq(dsi, 0x8a, 0x12);
	dsi_dcs_write_seq(dsi, 0x95, 0xb9);
	dsi_dcs_write_seq(dsi, 0x96, 0xb9);
	dsi_dcs_write_seq(dsi, 0x97, 0xb9);
	dsi_dcs_write_seq(dsi, 0x98, 0xb9);
	dsi_dcs_write_seq(dsi, 0xff, 0x24);
	dsi_dcs_write_seq(dsi, 0xfb, 0x01);
	dsi_dcs_write_seq(dsi, 0x00, 0x1c);
	dsi_dcs_write_seq(dsi, 0x01, 0x1c);
	dsi_dcs_write_seq(dsi, 0x02, 0x1c);
	dsi_dcs_write_seq(dsi, 0x03, 0x1c);
	dsi_dcs_write_seq(dsi, MIPI_DCS_GET_DISPLAY_ID, 0x20);
	dsi_dcs_write_seq(dsi, 0x05, 0x00);
	dsi_dcs_write_seq(dsi, MIPI_DCS_GET_RED_CHANNEL, 0x09);
	dsi_dcs_write_seq(dsi, MIPI_DCS_GET_GREEN_CHANNEL, 0x0a);
	dsi_dcs_write_seq(dsi, MIPI_DCS_GET_BLUE_CHANNEL, 0x1e);
	dsi_dcs_write_seq(dsi, MIPI_DCS_GET_DISPLAY_STATUS, 0x0d);
	dsi_dcs_write_seq(dsi, MIPI_DCS_GET_POWER_MODE, 0x0d);
	dsi_dcs_write_seq(dsi, MIPI_DCS_GET_ADDRESS_MODE, 0x25);
	dsi_dcs_write_seq(dsi, MIPI_DCS_GET_PIXEL_FORMAT, 0x24);
	dsi_dcs_write_seq(dsi, MIPI_DCS_GET_DISPLAY_MODE, 0x01);
	dsi_dcs_write_seq(dsi, MIPI_DCS_GET_SIGNAL_MODE, 0x04);
	dsi_dcs_write_seq(dsi, MIPI_DCS_GET_DIAGNOSTIC_RESULT, 0x04);
	dsi_dcs_write_seq(dsi, 0x10, 0x03);
	dsi_dcs_write_seq(dsi, 0x11, 0x03);
	dsi_dcs_write_seq(dsi, 0x12, 0x14);
	dsi_dcs_write_seq(dsi, 0x13, 0x14);
	dsi_dcs_write_seq(dsi, 0x14, 0x12);
	dsi_dcs_write_seq(dsi, 0x15, 0x12);
	dsi_dcs_write_seq(dsi, 0x16, 0x10);
	dsi_dcs_write_seq(dsi, 0x17, 0x1c);
	dsi_dcs_write_seq(dsi, 0x18, 0x1c);
	dsi_dcs_write_seq(dsi, 0x19, 0x1c);
	dsi_dcs_write_seq(dsi, 0x1a, 0x1c);
	dsi_dcs_write_seq(dsi, 0x1b, 0x20);
	dsi_dcs_write_seq(dsi, 0x1c, 0x0d);
	dsi_dcs_write_seq(dsi, 0x1d, 0x09);
	dsi_dcs_write_seq(dsi, 0x1e, 0x0a);
	dsi_dcs_write_seq(dsi, 0x1f, 0x1e);
	dsi_dcs_write_seq(dsi, 0x20, 0x0d);
	dsi_dcs_write_seq(dsi, 0x21, 0x0d);
	dsi_dcs_write_seq(dsi, 0x22, 0x25);
	dsi_dcs_write_seq(dsi, 0x23, 0x24);
	dsi_dcs_write_seq(dsi, 0x24, 0x01);
	dsi_dcs_write_seq(dsi, 0x25, 0x04);
	dsi_dcs_write_seq(dsi, MIPI_DCS_SET_GAMMA_CURVE, 0x04);
	dsi_dcs_write_seq(dsi, 0x27, 0x03);
	dsi_dcs_write_seq(dsi, 0x28, 0x03);
	dsi_dcs_write_seq(dsi, 0x29, 0x14);
	dsi_dcs_write_seq(dsi, 0x2a, 0x14);
	dsi_dcs_write_seq(dsi, 0x2b, 0x12);
	dsi_dcs_write_seq(dsi, MIPI_DCS_WRITE_LUT, 0x12);
	dsi_dcs_write_seq(dsi, 0x2f, 0x10);
	dsi_dcs_write_seq(dsi, 0x31, 0x02);
	dsi_dcs_write_seq(dsi, 0x32, 0x03);
	dsi_dcs_write_seq(dsi, 0x33, 0x04);
	dsi_dcs_write_seq(dsi, 0x34, 0x02);
	dsi_dcs_write_seq(dsi, 0x37, 0x09);
	dsi_dcs_write_seq(dsi, 0x38, 0x6a);
	dsi_dcs_write_seq(dsi, 0x39, 0x6a);
	dsi_dcs_write_seq(dsi, 0x3f, 0x6a);
	dsi_dcs_write_seq(dsi, 0x41, 0x02);
	dsi_dcs_write_seq(dsi, 0x42, 0x03);
	dsi_dcs_write_seq(dsi, 0x4c, 0x10);
	dsi_dcs_write_seq(dsi, 0x4d, 0x10);
	dsi_dcs_write_seq(dsi, 0x60, 0x90);
	dsi_dcs_write_seq(dsi, 0x61, 0xd8);
	dsi_dcs_write_seq(dsi, 0x72, 0x00);
	dsi_dcs_write_seq(dsi, 0x73, 0x00);
	dsi_dcs_write_seq(dsi, 0x74, 0x00);
	dsi_dcs_write_seq(dsi, 0x75, 0x00);
	dsi_dcs_write_seq(dsi, 0x79, 0x23);
	dsi_dcs_write_seq(dsi, 0x7a, 0x0d);
	dsi_dcs_write_seq(dsi, 0x7b, 0x98);
	dsi_dcs_write_seq(dsi, 0x7c, 0x80);
	dsi_dcs_write_seq(dsi, 0x7d, 0x09);
	dsi_dcs_write_seq(dsi, 0x80, 0x42);
	dsi_dcs_write_seq(dsi, 0x82, 0x11);
	dsi_dcs_write_seq(dsi, 0x83, 0x22);
	dsi_dcs_write_seq(dsi, 0x84, 0x33);
	dsi_dcs_write_seq(dsi, 0x85, 0x00);
	dsi_dcs_write_seq(dsi, 0x86, 0x00);
	dsi_dcs_write_seq(dsi, 0x87, 0x00);
	dsi_dcs_write_seq(dsi, 0x88, 0x11);
	dsi_dcs_write_seq(dsi, 0x89, 0x22);
	dsi_dcs_write_seq(dsi, 0x8a, 0x33);
	dsi_dcs_write_seq(dsi, 0x8b, 0x00);
	dsi_dcs_write_seq(dsi, 0x8c, 0x00);
	dsi_dcs_write_seq(dsi, 0x8d, 0x00);
	dsi_dcs_write_seq(dsi, 0x92, 0x6d);
	dsi_dcs_write_seq(dsi, 0x9d, 0xb6);
	dsi_dcs_write_seq(dsi, 0xb3, 0x02);
	dsi_dcs_write_seq(dsi, 0xb4, 0x00);
	dsi_dcs_write_seq(dsi, 0xdc, 0x44);
	dsi_dcs_write_seq(dsi, 0xdd, 0x03);
	dsi_dcs_write_seq(dsi, 0xdf, 0x3e);
	dsi_dcs_write_seq(dsi, 0xe0, 0x3e);
	dsi_dcs_write_seq(dsi, 0xe1, 0x22);
	dsi_dcs_write_seq(dsi, 0xe2, 0x24);
	dsi_dcs_write_seq(dsi, 0xe3, 0x09);
	dsi_dcs_write_seq(dsi, 0xe4, 0x09);
	dsi_dcs_write_seq(dsi, 0xeb, 0x0f);
	dsi_dcs_write_seq(dsi, 0xff, 0x25);
	dsi_dcs_write_seq(dsi, 0xfb, 0x01);
	dsi_dcs_write_seq(dsi, 0x21, 0x18);
	dsi_dcs_write_seq(dsi, 0x22, 0x18);
	dsi_dcs_write_seq(dsi, 0x24, 0x6d);
	dsi_dcs_write_seq(dsi, 0x25, 0x6d);
	dsi_dcs_write_seq(dsi, 0x2f, 0x10);
	dsi_dcs_write_seq(dsi, MIPI_DCS_SET_PARTIAL_ROWS, 0x2d);
	dsi_dcs_write_seq(dsi, 0x38, 0x2d);
	dsi_dcs_write_seq(dsi, 0x3f, 0x21);
	dsi_dcs_write_seq(dsi, 0x40, 0x65);
	dsi_dcs_write_seq(dsi, 0x4b, 0x21);
	dsi_dcs_write_seq(dsi, 0x4c, 0x65);
	dsi_dcs_write_seq(dsi, 0x58, 0x22);
	dsi_dcs_write_seq(dsi, 0x59, 0x04);
	dsi_dcs_write_seq(dsi, 0x5a, 0x09);
	dsi_dcs_write_seq(dsi, 0x5b, 0x09);
	dsi_dcs_write_seq(dsi, 0x5c, 0x25);
	dsi_dcs_write_seq(dsi, MIPI_DCS_SET_CABC_MIN_BRIGHTNESS, 0xff);
	dsi_dcs_write_seq(dsi, MIPI_DCS_GET_CABC_MIN_BRIGHTNESS, 0x28);
	dsi_dcs_write_seq(dsi, 0x66, 0xd8);
	dsi_dcs_write_seq(dsi, 0x67, 0x2b);
	dsi_dcs_write_seq(dsi, 0x68, 0x58);
	dsi_dcs_write_seq(dsi, 0x6b, 0x00);
	dsi_dcs_write_seq(dsi, 0x6c, 0x6d);
	dsi_dcs_write_seq(dsi, 0x77, 0x72);
	dsi_dcs_write_seq(dsi, 0xbf, 0x00);
	dsi_dcs_write_seq(dsi, 0xc3, 0x01);
	dsi_dcs_write_seq(dsi, 0xff, 0x26);
	dsi_dcs_write_seq(dsi, 0xfb, 0x01);
	dsi_dcs_write_seq(dsi, MIPI_DCS_GET_RED_CHANNEL, 0xff);
	dsi_dcs_write_seq(dsi, MIPI_DCS_GET_PIXEL_FORMAT, 0x11);
	dsi_dcs_write_seq(dsi, MIPI_DCS_GET_DIAGNOSTIC_RESULT, 0x09);
	dsi_dcs_write_seq(dsi, 0x10, 0x0a);
	dsi_dcs_write_seq(dsi, 0x12, 0x8c);
	dsi_dcs_write_seq(dsi, 0x1a, 0x28);
	dsi_dcs_write_seq(dsi, 0x1c, 0xaf);
	dsi_dcs_write_seq(dsi, 0x1e, 0xab);
	dsi_dcs_write_seq(dsi, 0x98, 0xf1);
	dsi_dcs_write_seq(dsi, 0xa9, 0x12);
	dsi_dcs_write_seq(dsi, 0xaa, 0x10);
	dsi_dcs_write_seq(dsi, 0xae, 0x6a);
	dsi_dcs_write_seq(dsi, 0xff, 0x27);
	dsi_dcs_write_seq(dsi, 0xfb, 0x01);
	dsi_dcs_write_seq(dsi, 0x13, 0x00);
	dsi_dcs_write_seq(dsi, 0x1e, 0x24);
	dsi_dcs_write_seq(dsi, 0xff, 0xf0);
	dsi_dcs_write_seq(dsi, 0xfb, 0x01);
	dsi_dcs_write_seq(dsi, 0xa2, 0x00);
	dsi_dcs_write_seq(dsi, 0xff, 0x20);
	dsi_dcs_write_seq(dsi, 0xfb, 0x01);
	dsi_dcs_write_seq(dsi, 0xb0,
			  0x00, 0x00, 0x00, 0x3d, 0x00, 0x74, 0x00, 0x9a, 0x00,
			  0xb9, 0x00, 0xd1, 0x00, 0xe6, 0x00, 0xf8);
	dsi_dcs_write_seq(dsi, 0xb1,
			  0x01, 0x08, 0x01, 0x3b, 0x01, 0x5e, 0x01, 0x95, 0x01,
			  0xbb, 0x01, 0xf8, 0x02, 0x23, 0x02, 0x25);
	dsi_dcs_write_seq(dsi, 0xb2,
			  0x02, 0x51, 0x02, 0x84, 0x02, 0xab, 0x02, 0xe1, 0x02,
			  0xfb, 0x03, 0x30, 0x03, 0x3e, 0x03, 0x4d);
	dsi_dcs_write_seq(dsi, 0xb3,
			  0x03, 0x5f, 0x03, 0x72, 0x03, 0x8a, 0x03, 0xa9, 0x03,
			  0xc9, 0x03, 0xff);
	dsi_dcs_write_seq(dsi, 0xb4,
			  0x00, 0x00, 0x00, 0x3d, 0x00, 0x74, 0x00, 0x9a, 0x00,
			  0xb9, 0x00, 0xd1, 0x00, 0xe6, 0x00, 0xf8);
	dsi_dcs_write_seq(dsi, 0xb5,
			  0x01, 0x08, 0x01, 0x3b, 0x01, 0x5e, 0x01, 0x95, 0x01,
			  0xbb, 0x01, 0xf8, 0x02, 0x23, 0x02, 0x25);
	dsi_dcs_write_seq(dsi, 0xb6,
			  0x02, 0x51, 0x02, 0x84, 0x02, 0xab, 0x02, 0xe1, 0x02,
			  0xfb, 0x03, 0x30, 0x03, 0x3e, 0x03, 0x4d);
	dsi_dcs_write_seq(dsi, 0xb7,
			  0x03, 0x5f, 0x03, 0x72, 0x03, 0x8a, 0x03, 0xa9, 0x03,
			  0xc9, 0x03, 0xff);
	dsi_dcs_write_seq(dsi, 0xb8,
			  0x00, 0x00, 0x00, 0x3d, 0x00, 0x74, 0x00, 0x9a, 0x00,
			  0xb9, 0x00, 0xd1, 0x00, 0xe6, 0x00, 0xf8);
	dsi_dcs_write_seq(dsi, 0xb9,
			  0x01, 0x08, 0x01, 0x3b, 0x01, 0x5e, 0x01, 0x95, 0x01,
			  0xbb, 0x01, 0xf8, 0x02, 0x23, 0x02, 0x25);
	dsi_dcs_write_seq(dsi, 0xba,
			  0x02, 0x51, 0x02, 0x84, 0x02, 0xab, 0x02, 0xe1, 0x02,
			  0xfb, 0x03, 0x30, 0x03, 0x3e, 0x03, 0x4d);
	dsi_dcs_write_seq(dsi, 0xbb,
			  0x03, 0x5f, 0x03, 0x72, 0x03, 0x8a, 0x03, 0xa9, 0x03,
			  0xc9, 0x03, 0xff);
	dsi_dcs_write_seq(dsi, 0xff, 0x21);
	dsi_dcs_write_seq(dsi, 0xfb, 0x01);
	dsi_dcs_write_seq(dsi, 0xb0,
			  0x00, 0x00, 0x00, 0x3d, 0x00, 0x74, 0x00, 0x9a, 0x00,
			  0xb9, 0x00, 0xd1, 0x00, 0xe6, 0x00, 0xf8);
	dsi_dcs_write_seq(dsi, 0xb1,
			  0x01, 0x08, 0x01, 0x3b, 0x01, 0x5e, 0x01, 0x95, 0x01,
			  0xbb, 0x01, 0xf8, 0x02, 0x23, 0x02, 0x25);
	dsi_dcs_write_seq(dsi, 0xb2,
			  0x02, 0x51, 0x02, 0x84, 0x02, 0xab, 0x02, 0xe1, 0x02,
			  0xfb, 0x03, 0x30, 0x03, 0x3e, 0x03, 0x4d);
	dsi_dcs_write_seq(dsi, 0xb3,
			  0x03, 0x5f, 0x03, 0x72, 0x03, 0x8a, 0x03, 0xa9, 0x03,
			  0xc9, 0x03, 0xff);
	dsi_dcs_write_seq(dsi, 0xb4,
			  0x00, 0x00, 0x00, 0x3d, 0x00, 0x74, 0x00, 0x9a, 0x00,
			  0xb9, 0x00, 0xd1, 0x00, 0xe6, 0x00, 0xf8);
	dsi_dcs_write_seq(dsi, 0xb5,
			  0x01, 0x08, 0x01, 0x3b, 0x01, 0x5e, 0x01, 0x95, 0x01,
			  0xbb, 0x01, 0xf8, 0x02, 0x23, 0x02, 0x25);
	dsi_dcs_write_seq(dsi, 0xb6,
			  0x02, 0x51, 0x02, 0x84, 0x02, 0xab, 0x02, 0xe1, 0x02,
			  0xfb, 0x03, 0x30, 0x03, 0x3e, 0x03, 0x4d);
	dsi_dcs_write_seq(dsi, 0xb7,
			  0x03, 0x5f, 0x03, 0x72, 0x03, 0x8a, 0x03, 0xa9, 0x03,
			  0xc9, 0x03, 0xff);
	dsi_dcs_write_seq(dsi, 0xb8,
			  0x00, 0x00, 0x00, 0x3d, 0x00, 0x74, 0x00, 0x9a, 0x00,
			  0xb9, 0x00, 0xd1, 0x00, 0xe6, 0x00, 0xf8);
	dsi_dcs_write_seq(dsi, 0xb9,
			  0x01, 0x08, 0x01, 0x3b, 0x01, 0x5e, 0x01, 0x95, 0x01,
			  0xbb, 0x01, 0xf8, 0x02, 0x23, 0x02, 0x25);
	dsi_dcs_write_seq(dsi, 0xba,
			  0x02, 0x51, 0x02, 0x84, 0x02, 0xab, 0x02, 0xe1, 0x02,
			  0xfb, 0x03, 0x30, 0x03, 0x3e, 0x03, 0x4d);
	dsi_dcs_write_seq(dsi, 0xbb,
			  0x03, 0x5f, 0x03, 0x72, 0x03, 0x8a, 0x03, 0xa9, 0x03,
			  0xc9, 0x03, 0xff);
	dsi_dcs_write_seq(dsi, 0xff, 0x10);
	dsi_dcs_write_seq(dsi, 0xfb, 0x01);

	ret = mipi_dsi_dcs_exit_sleep_mode(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to exit sleep mode: %d\n", ret);
		return ret;
	}
	msleep(120);

	ret = mipi_dsi_dcs_set_display_on(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to set display on: %d\n", ret);
		return ret;
	}
	msleep(50);

	return 0;
}

static int nt36672a_truly_fhdplus_off(struct nt36672a_truly_fhdplus *ctx)
{
	struct mipi_dsi_device *dsi = ctx->dsi;
	struct device *dev = &dsi->dev;
	int ret;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_set_display_off(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to set display off: %d\n", ret);
		return ret;
	}

	ret = mipi_dsi_dcs_enter_sleep_mode(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to enter sleep mode: %d\n", ret);
		return ret;
	}
	msleep(80);

	return 0;
}

static int nt36672a_truly_fhdplus_prepare(struct drm_panel *panel)
{
	struct nt36672a_truly_fhdplus *ctx = to_nt36672a_truly_fhdplus(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	if (ctx->prepared)
		return 0;

	ret = regulator_bulk_enable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
	if (ret < 0) {
		dev_err(dev, "Failed to enable regulators: %d\n", ret);
		return ret;
	}

	nt36672a_truly_fhdplus_reset(ctx);

	ret = nt36672a_truly_fhdplus_on(ctx);
	if (ret < 0) {
		dev_err(dev, "Failed to initialize panel: %d\n", ret);
		gpiod_set_value_cansleep(ctx->reset_gpio, 0);
		regulator_bulk_disable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
		return ret;
	}

	ctx->prepared = true;
	return 0;
}

static int nt36672a_truly_fhdplus_unprepare(struct drm_panel *panel)
{
	struct nt36672a_truly_fhdplus *ctx = to_nt36672a_truly_fhdplus(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	if (!ctx->prepared)
		return 0;

	ret = nt36672a_truly_fhdplus_off(ctx);
	if (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	regulator_bulk_disable(ARRAY_SIZE(ctx->supplies), ctx->supplies);

	ctx->prepared = false;
	return 0;
}

static const struct drm_display_mode nt36672a_truly_fhdplus_mode = {
	.clock = (1080 + 25 + 12 + 120) * (2520 + 12 + 4 + 10) * 60 / 1000,
	.hdisplay = 1080,
	.hsync_start = 1080 + 25,
	.hsync_end = 1080 + 25 + 12,
	.htotal = 1080 + 25 + 12 + 120,
	.vdisplay = 2520,
	.vsync_start = 2520 + 12,
	.vsync_end = 2520 + 12 + 4,
	.vtotal = 2520 + 12 + 4 + 10,
	.vrefresh = 60,
	.width_mm = 60,
	.height_mm = 139,
};

static int nt36672a_truly_fhdplus_get_modes(struct drm_panel *panel,
					    struct drm_connector *connector)
{
	struct drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &nt36672a_truly_fhdplus_mode);
	if (!mode)
		return -ENOMEM;

	drm_mode_set_name(mode);

	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	connector->display_info.width_mm = mode->width_mm;
	connector->display_info.height_mm = mode->height_mm;
	drm_mode_probed_add(connector, mode);

	return 1;
}

static const struct drm_panel_funcs nt36672a_truly_fhdplus_panel_funcs = {
	.prepare = nt36672a_truly_fhdplus_prepare,
	.unprepare = nt36672a_truly_fhdplus_unprepare,
	.get_modes = nt36672a_truly_fhdplus_get_modes,
};

static int nt36672a_truly_fhdplus_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct nt36672a_truly_fhdplus *ctx;
	int ret;

	ctx = devm_kzalloc(dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->supplies[0].supply = "vdd";
	ctx->supplies[1].supply = "vddio";
	ctx->supplies[2].supply = "vsn";
	ctx->supplies[3].supply = "vsp";
	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(ctx->supplies),
				      ctx->supplies);
	if (ret < 0) {
		dev_err(dev, "Failed to get regulators: %d\n", ret);
		return ret;
	}

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(ctx->reset_gpio)) {
		ret = PTR_ERR(ctx->reset_gpio);
		dev_err(dev, "Failed to get reset-gpios: %d\n", ret);
		return ret;
	}

	ctx->dsi = dsi;
	mipi_dsi_set_drvdata(dsi, ctx);

	dsi->lanes = 4;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
			  MIPI_DSI_CLOCK_NON_CONTINUOUS;

	drm_panel_init(&ctx->panel, dev, &nt36672a_truly_fhdplus_panel_funcs,
		       DRM_MODE_CONNECTOR_DSI);

	ret = drm_panel_of_backlight(&ctx->panel);
	if (ret) {
		dev_err(dev, "Failed to get backlight: %d\n", ret);
		return ret;
	}

	ret = drm_panel_add(&ctx->panel);
	if (ret < 0) {
		dev_err(dev, "Failed to add panel: %d\n", ret);
		return ret;
	}

	ret = mipi_dsi_attach(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to attach to DSI host: %d\n", ret);
		return ret;
	}

	return 0;
}

static int nt36672a_truly_fhdplus_remove(struct mipi_dsi_device *dsi)
{
	struct nt36672a_truly_fhdplus *ctx = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_remove(&ctx->panel);

	return 0;
}

static const struct of_device_id nt36672a_truly_fhdplus_of_match[] = {
	{ .compatible = "mdss,nt36672a-truly-fhdplus" }, // FIXME
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, nt36672a_truly_fhdplus_of_match);

static struct mipi_dsi_driver nt36672a_truly_fhdplus_driver = {
	.probe = nt36672a_truly_fhdplus_probe,
	.remove = nt36672a_truly_fhdplus_remove,
	.driver = {
		.name = "panel-nt36672a-truly-fhdplus",
		.of_match_table = nt36672a_truly_fhdplus_of_match,
	},
};
module_mipi_dsi_driver(nt36672a_truly_fhdplus_driver);

MODULE_AUTHOR("linux-mdss-dsi-panel-driver-generator <fix@me>"); // FIXME
MODULE_DESCRIPTION("DRM driver for 1");
MODULE_LICENSE("GPL v2");
