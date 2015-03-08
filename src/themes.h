#pragma once

typedef struct {
  const int resource_id;
  const int text_time_color;
  const int text_date_color;
} Theme;

static const int BACKGROUND_COUNT = 5;

static const Theme themes[] = {
  {
    .resource_id = RESOURCE_ID_IMAGE_BG_2,
    .text_time_color = 0xffffff,
    .text_date_color = 0xffffff
  }, {
    .resource_id = RESOURCE_ID_IMAGE_BG_3,
    .text_time_color = 0xffffff,
    .text_date_color = 0xffffff
  }, {
    .resource_id = RESOURCE_ID_IMAGE_BG_4,
    .text_time_color = 0x000000,
    .text_date_color = 0x000000
  }, {
    .resource_id = RESOURCE_ID_IMAGE_BG_5,
    .text_time_color = 0x000000,
    .text_date_color = 0x000000
  }, {
    .resource_id = RESOURCE_ID_IMAGE_BG_8,
    .text_time_color = 0xAAAA00,
    .text_date_color = 0xffffff
  }
};