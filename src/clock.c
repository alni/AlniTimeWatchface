#include "clock.h"
#include <pebble.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GBitmap *s_res_image_bg_2;
static GFont s_res_bitham_42_medium_numbers;
static GFont s_res_gothic_18_bold;
static BitmapLayer *s_bitmaplayer_1;
static TextLayer *s_textlayer_time;
static TextLayer *s_textlayer_date;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorClear);
  window_set_fullscreen(s_window, true);
  
  s_res_image_bg_2 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG_2);
  s_res_bitham_42_medium_numbers = fonts_get_system_font(FONT_KEY_BITHAM_42_MEDIUM_NUMBERS);
  s_res_gothic_18_bold = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
  // s_bitmaplayer_1
  s_bitmaplayer_1 = bitmap_layer_create(GRect(0, 0, 144, 168));
  bitmap_layer_set_bitmap(s_bitmaplayer_1, s_res_image_bg_2);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_1);
  
  // s_textlayer_time
  s_textlayer_time = text_layer_create(GRect(13, 42, 119, 43));
  text_layer_set_background_color(s_textlayer_time, GColorBlack);
  text_layer_set_text_color(s_textlayer_time, GColorWhite);
  text_layer_set_text(s_textlayer_time, "00:00");
  text_layer_set_text_alignment(s_textlayer_time, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_time, s_res_bitham_42_medium_numbers);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_time);
  
  // s_textlayer_date
  s_textlayer_date = text_layer_create(GRect(13, 87, 96, 20));
  text_layer_set_background_color(s_textlayer_date, GColorBlack);
  text_layer_set_text_color(s_textlayer_date, GColorWhite);
  text_layer_set_text(s_textlayer_date, "Xxxxxxxxx 00");
  text_layer_set_text_alignment(s_textlayer_date, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_date, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_date);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  bitmap_layer_destroy(s_bitmaplayer_1);
  text_layer_destroy(s_textlayer_time);
  text_layer_destroy(s_textlayer_date);
  gbitmap_destroy(s_res_image_bg_2);
}
// END AUTO-GENERATED UI CODE

static void handle_minute_tick(struct tm *tick_time, TimeUnits units_changed) {
  // Need to be static because they're used by the system later.
  static char s_time_text[] = "00:00";
  static char s_date_text[] = "Xxxxxxxxx 00";

  strftime(s_date_text, sizeof(s_date_text), "%B %e", tick_time);
  text_layer_set_text(s_textlayer_date, s_date_text);

  char *time_format;
  if (clock_is_24h_style()) {
    time_format = "%R";
  } else {
    time_format = "%I:%M";
  }
  strftime(s_time_text, sizeof(s_time_text), time_format, tick_time);

  // Handle lack of non-padded hour format string for twelve hour clock.
  if (!clock_is_24h_style() && (s_time_text[0] == '0')) {
    memmove(s_time_text, &s_time_text[1], sizeof(s_time_text) - 1);
  }
  text_layer_set_text(s_textlayer_time, s_time_text);
}

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_clock(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
  
  tick_timer_service_subscribe(MINUTE_UNIT, handle_minute_tick);
  
  // Prevent starting blank
  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  handle_minute_tick(t, MINUTE_UNIT);
}

void hide_clock(void) {
  window_stack_remove(s_window, true);
}

int main() {
  show_clock();
  app_event_loop();
  hide_clock();
}
