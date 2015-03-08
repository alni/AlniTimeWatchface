#include "clock.h"
#include <pebble.h>
#include "themes.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GBitmap *s_res_image_bg_2;
static GFont s_res_bitham_42_medium_numbers;
static GFont s_res_gothic_18_bold;
static BitmapLayer *s_bitmaplayer_1;
static BitmapLayer *s_bitmaplayer_2;
static TextLayer *s_textlayer_time;
static TextLayer *s_textlayer_date;
static TextLayer *s_textlayer_time_2;

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
  
  // s_bitmaplayer_2
  s_bitmaplayer_2 = bitmap_layer_create(GRect(0, 34, 144, 74));
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_2);
  
  // s_textlayer_time
  s_textlayer_time = text_layer_create(GRect(0, 42, 135, 43));
  text_layer_set_background_color(s_textlayer_time, GColorClear);
  text_layer_set_text_color(s_textlayer_time, GColorWhite);
  text_layer_set_text(s_textlayer_time, "00:00");
  text_layer_set_text_alignment(s_textlayer_time, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_time, s_res_bitham_42_medium_numbers);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_time);
  
  // s_textlayer_date
  s_textlayer_date = text_layer_create(GRect(13, 87, 96, 20));
  text_layer_set_background_color(s_textlayer_date, GColorClear);
  text_layer_set_text_color(s_textlayer_date, GColorWhite);
  text_layer_set_text(s_textlayer_date, "Xxxxxxxxx 00");
  text_layer_set_text_alignment(s_textlayer_date, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_date, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_date);
  
  // s_textlayer_time_2
  s_textlayer_time_2 = text_layer_create(GRect(144, 42, 135, 43));
  text_layer_set_background_color(s_textlayer_time_2, GColorClear);
  text_layer_set_text_color(s_textlayer_time_2, GColorWhite);
  text_layer_set_text(s_textlayer_time_2, "00:00");
  text_layer_set_text_alignment(s_textlayer_time_2, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_time_2, s_res_bitham_42_medium_numbers);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_time_2);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  bitmap_layer_destroy(s_bitmaplayer_1);
  bitmap_layer_destroy(s_bitmaplayer_2);
  text_layer_destroy(s_textlayer_time);
  text_layer_destroy(s_textlayer_date);
  text_layer_destroy(s_textlayer_time_2);
  gbitmap_destroy(s_res_image_bg_2);
}
// END AUTO-GENERATED UI CODE

typedef struct {
	TextLayer *currentLayer;
	TextLayer *nextLayer;	
	PropertyAnimation *currentAnimation;
	PropertyAnimation *nextAnimation;
} Line;






static time_t last_tapped = -1;

static int current_bg_image = 0;

static void set_container_image(GBitmap **bmp_image, BitmapLayer *bmp_layer, const int resource_id, GPoint origin) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "resource_id: %d", resource_id);
  GBitmap *old_image = *bmp_image;
  if (old_image != NULL) {
    gbitmap_destroy(old_image);
  }
  *bmp_image = gbitmap_create_with_resource(resource_id);
  #ifdef PBL_PLATFORM_BASALT
    GRect bitmap_bounds = gbitmap_get_bounds((*bmp_image));
  #else
    GRect bitmap_bounds = (*bmp_image)->bounds;
  #endif
  GRect frame = GRect(origin.x, origin.y, bitmap_bounds.size.w, bitmap_bounds.size.h);
  bitmap_layer_set_bitmap(bmp_layer, *bmp_image);
  layer_set_frame(bitmap_layer_get_layer(bmp_layer), frame);
  
}

static void setBackgroundImage(int increment) {
  int next_index = current_bg_image+increment;
  if (next_index >= BACKGROUND_COUNT) {
    next_index = 0;
  } else if (next_index < 0) {
    next_index = BACKGROUND_COUNT - 1;
  }
  current_bg_image = next_index;
  Theme theme = themes[current_bg_image];
  APP_LOG(APP_LOG_LEVEL_DEBUG, "next_index: %d", current_bg_image);
  set_container_image(&s_res_image_bg_2, s_bitmaplayer_1, theme.resource_id, GPoint(0, 0));
  
  //bitmap_layer_set_background_color(s_bitmaplayer_2, GColorFromHEX(theme.text_bg_color));
  
  //text_layer_set_background_color(s_textlayer_time, GColorFromHEX(theme.text_bg_color));
  text_layer_set_text_color(s_textlayer_time, GColorFromHEX(theme.text_time_color));
  
  //text_layer_set_background_color(s_textlayer_time_2, GColorFromHEX(theme.text_bg_color));
  text_layer_set_text_color(s_textlayer_time_2, GColorFromHEX(theme.text_time_color));
  
  //text_layer_set_background_color(s_textlayer_date, GColorFromHEX(theme.text_bg_color));
  text_layer_set_text_color(s_textlayer_date, GColorFromHEX(theme.text_date_color));
  //set_container_image(&s_res_image_bg_2, s_bitmaplayer_1, BACKGROUND_IMAGE_RESOURCE_IDS[current_bg_image], GPoint(0, 0));
}


static void tap_handler(AccelAxisType axis, int32_t direction) {
  time_t now;
  switch (axis) {
  case ACCEL_AXIS_X:
    if (direction > 0) {
      APP_LOG(APP_LOG_LEVEL_INFO, "X axis positive.");
    } else {
      APP_LOG(APP_LOG_LEVEL_INFO, "X axis negative.");
    }
    break;
  case ACCEL_AXIS_Y:
    now = time(NULL);
    if (last_tapped == -1 || now - last_tapped >= 1) {
      if (direction > 0) {
        setBackgroundImage(1);
        APP_LOG(APP_LOG_LEVEL_INFO, "Y axis positive.");
      } else {
        setBackgroundImage(-1);
        APP_LOG(APP_LOG_LEVEL_INFO, "Y axis negative.");
      }
    }
    last_tapped = now;
    break;
  case ACCEL_AXIS_Z:
    if (direction > 0) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Z axis positive.");
    } else {
      APP_LOG(APP_LOG_LEVEL_INFO, "Z axis negative.");
    }
    break;
  }
}





static Line line1;
static Line line2;

// Animation handler
static void animationStoppedHandler(struct Animation *animation, bool finished, void *context)
{
	Layer *textLayer = text_layer_get_layer((TextLayer *)context);
	GRect rect = layer_get_frame(textLayer);
	rect.origin.x = 144;
	layer_set_frame(textLayer, rect);
}


// Animate line
static void makeAnimationsForLayers(Line *line, TextLayer *current, TextLayer *next)
{
	GRect fromRect = layer_get_frame(text_layer_get_layer(next));
	GRect toRect = fromRect;
	toRect.origin.x -= 144;
	
	line->nextAnimation = property_animation_create_layer_frame(text_layer_get_layer(next), &fromRect, &toRect);
	animation_set_duration((Animation *)line->nextAnimation, 400);
	animation_set_curve((Animation *)line->nextAnimation, AnimationCurveEaseOut);
	animation_schedule((Animation *)line->nextAnimation);
	
	GRect fromRect2 = layer_get_frame(text_layer_get_layer(current));
	GRect toRect2 = fromRect2;
	toRect2.origin.x -= 144;
	
	line->currentAnimation = property_animation_create_layer_frame(text_layer_get_layer(current), &fromRect2, &toRect2);
	animation_set_duration((Animation *)line->currentAnimation, 400);
	animation_set_curve((Animation *)line->currentAnimation, AnimationCurveEaseOut);
	
	animation_set_handlers((Animation *)line->currentAnimation, (AnimationHandlers) {
		.stopped = (AnimationStoppedHandler)animationStoppedHandler
	}, current);
	
	animation_schedule((Animation *)line->currentAnimation);
}

// Update line
static void updateLineTo(Line *line, char *value)
{
	TextLayer *next, *current;
	
	GRect rect = layer_get_frame(text_layer_get_layer(line->currentLayer));
	current = (rect.origin.x == 0) ? line->currentLayer : line->nextLayer;
	next = (current == line->currentLayer) ? line->nextLayer : line->currentLayer;
	
	// Update correct text only
	if (current == line->currentLayer) {
		text_layer_set_text(next, value);
	} else {
		text_layer_set_text(next, value);
	}
	
	makeAnimationsForLayers(line, current, next);
}

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
  updateLineTo(&line1, s_time_text);
  //text_layer_set_text(s_textlayer_time, s_time_text);
}

static void handle_initial_minute_tick(struct tm *tick_time, TimeUnits units_changed) {
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
  text_layer_set_text(s_textlayer_time_2, s_time_text);
}

static void handle_window_load(Window *window) {
  
}

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_clock(void) {
  initialise_ui();
  
  // 1st line layers
	line1.currentLayer = s_textlayer_time;
	line1.nextLayer = s_textlayer_time_2;
  
  window_set_window_handlers(s_window, (WindowHandlers) {
    .load = handle_window_load,
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
  
  tick_timer_service_subscribe(MINUTE_UNIT, handle_minute_tick);
  accel_tap_service_subscribe(tap_handler);
  
  // Prevent starting blank
  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  handle_initial_minute_tick(t, MINUTE_UNIT);
}

void hide_clock(void) {
  tick_timer_service_unsubscribe();
  accel_tap_service_unsubscribe();
  window_stack_remove(s_window, true);
}

int main() {
  show_clock();
  app_event_loop();
  hide_clock();
}
