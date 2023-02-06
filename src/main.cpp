#include <M5Core2.h>
#include <lvgl.h>

#include "examples/lv_examples.h"   // only used for lvgl examples
// #include "demos/lv_demos.h"         // only used for lvgl demos

static const uint16_t screenWidth = 320;
static const uint16_t screenHeight = 240;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * 10];

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight);

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char* buf) {
  Serial.printf(buf);
  Serial.flush();
}
#endif

/* Display flushing */
void my_disp_flush(lv_disp_drv_t* disp, const lv_area_t* area, lv_color_t* color_p) {
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors((uint16_t*)&color_p->full, w*h, true);
  tft.endWrite();

  lv_disp_flush_ready(disp);
}

/* Read the touchpad */
void my_touchpad_read(lv_indev_drv_t* indev_driver, lv_indev_data_t* data) {
  Point p;

  if (!M5.Touch.ispressed()) {
    data->state = LV_INDEV_STATE_REL;
  } else {
    data->state = LV_INDEV_STATE_PR;
    p = M5.Touch.getPressPoint();

    /* Set the coordinates */
    data->point.x = p.x;
    data->point.y = p.y;

    Serial.print("Data x ");
    Serial.println(p.x);

    Serial.print("Data y ");
    Serial.println(p.y);
  }
}

void setup() {
  M5.begin();
  Serial.begin(115200);

  String LVGL_Arduino = "Hello Arduino! ";
  LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

  Serial.println(LVGL_Arduino);
  Serial.println("I am LVGL_Arduino");

#if LV_USE_LOG != 0
  lv_log_register_print_cb(my_print);
#endif

  lv_init();

  tft.begin();
  tft.setRotation(1);

  lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * 10);

  /* Initialize the display */
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  lv_disp_drv_register(&disp_drv);

  // /* Initialize the (dummy) input device driver */
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  // Uncomment only one of the following functions to run a example or demo
  // Examples
  // Examples in anim/lv_example_anim.h
  lv_example_anim_1();
  // lv_example_anim_2();
  // lv_example_anim_3();
  // lv_example_anim_timeline_1();

  // Examples in event/lv_example_event.h
  // lv_example_event_1();
  // lv_example_event_2();
  // lv_example_event_3();
  // lv_example_event_4();

  // Examples in get_started/lv_example_get_started.h
  // lv_example_get_started_1();
  // lv_example_get_started_2();
  // lv_example_get_started_3();
  // lv_example_get_started_4();

  // Examples in layouts/lv_example_layout.h
  // lv_example_flex_1();
  // lv_example_flex_2();
  // lv_example_flex_3();
  // lv_example_flex_4();
  // lv_example_flex_5();
  // lv_example_flex_6();
  // lv_example_grid_1();
  // lv_example_grid_2();
  // lv_example_grid_3();
  // lv_example_grid_4();
  // lv_example_grid_5();
  // lv_example_grid_6();

  // Examples in libs/lv_example_libs.h
  // lv_example_barcode_1();
  // lv_example_bmp_1();
  // lv_example_ffmpeg_1();
  // lv_example_ffmpeg_2();
  // lv_example_freetype_1();
  // lv_example_gif_1();
  // lv_example_png_1();
  // lv_example_qrcode_1();
  // lv_example_rlottie_1();
  // lv_example_rlottie_2();
  // lv_example_sjpg_1();
  // lv_example_tiny_ttf_1();
  // lv_example_tiny_ttf_2();

  // Examples in others/lv_example_others.h
  // lv_example_file_explorer_1();
  // lv_example_file_explorer_2();
  // lv_example_file_explorer_3();
  // lv_example_fragment_1();
  // lv_example_fragment_2();
  // lv_example_gridnav_1();
  // lv_example_gridnav_2();
  // lv_example_gridnav_3();
  // lv_example_gridnav_4();
  // lv_example_ime_pinyin_1();
  // lv_example_ime_pinyin_2();
  // lv_example_imgfont_1();
  // lv_example_monkey_1();
  // lv_example_monkey_2();
  // lv_example_monkey_3();
  // lv_example_msg_1();
  // lv_example_msg_2();
  // lv_example_msg_3();
  // lv_example_snapshot_1();

  // Examples in scroll/lv_example_scroll.h
  // lv_example_scroll_1();
  // lv_example_scroll_2();
  // lv_example_scroll_3();
  // lv_example_scroll_4();
  // lv_example_scroll_5();
  // lv_example_scroll_6();

  // Examples in styles/lv_example_style.h
  // lv_example_style_1();
  // lv_example_style_2();
  // lv_example_style_3();
  // lv_example_style_4();
  // lv_example_style_5();
  // lv_example_style_6();
  // lv_example_style_7();
  // lv_example_style_8();
  // lv_example_style_9();
  // lv_example_style_10();
  // lv_example_style_11();
  // lv_example_style_12();
  // lv_example_style_13();
  // lv_example_style_14();
  // lv_example_style_15();

  // Examples in widgets/lv_example_widgets.h
  // lv_example_animimg_1();
  // lv_example_arc_1();
  // lv_example_arc_2();
  // lv_example_bar_1();
  // lv_example_bar_2();
  // lv_example_bar_3();
  // lv_example_bar_4();
  // lv_example_bar_5();
  // lv_example_bar_6();
  // lv_example_btn_1();
  // lv_example_btn_2();
  // lv_example_btn_3();
  // lv_example_btnmatrix_1();
  // lv_example_btnmatrix_2();
  // lv_example_btnmatrix_3();
  // lv_example_calendar_1();
  // lv_example_canvas_1();
  // lv_example_canvas_2();
  // lv_example_canvas_3();
  // lv_example_canvas_4();
  // lv_example_canvas_5();
  // lv_example_canvas_6();
  // lv_example_canvas_7();
  // lv_example_chart_1();
  // lv_example_chart_2();
  // lv_example_chart_3();
  // lv_example_chart_4();
  // lv_example_chart_5();
  // lv_example_chart_6();
  // lv_example_chart_7();
  // lv_example_chart_8();
  // lv_example_chart_9();
  // lv_example_checkbox_1();
  // lv_example_checkbox_2();
  // lv_example_colorwheel_1();
  // lv_example_dropdown_1();
  // lv_example_dropdown_2();
  // lv_example_dropdown_3();
  // lv_example_img_1();
  // lv_example_img_2();
  // lv_example_img_3();
  // lv_example_img_4();
  // lv_example_imgbtn_1();
  // lv_example_keyboard_1();
  // lv_example_keyboard_2();
  // lv_example_label_1();
  // lv_example_label_2();
  // lv_example_label_3();
  // lv_example_label_4();
  // lv_example_label_5();
  // lv_example_led_1();
  // lv_example_line_1();
  // lv_example_list_1();
  // lv_example_list_2();
  // lv_example_menu_1();
  // lv_example_menu_2();
  // lv_example_menu_3();
  // lv_example_menu_4();
  // lv_example_menu_5();
  // lv_example_meter_1();
  // lv_example_meter_2();
  // lv_example_meter_3();
  // lv_example_meter_4();
  // lv_example_msgbox_1();
  // lv_example_obj_1();
  // lv_example_obj_2();
  // lv_example_roller_1();
  // lv_example_roller_2();
  // lv_example_roller_3();
  // lv_example_slider_1();
  // lv_example_slider_2();
  // lv_example_slider_3();
  // lv_example_span_1();
  // lv_example_spinbox_1();
  // lv_example_spinner_1();
  // lv_example_switch_1();
  // lv_example_table_1();
  // lv_example_table_2();
  // lv_example_tabview_1();
  // lv_example_tabview_2();
  // lv_example_textarea_1();
  // lv_example_textarea_2();
  // lv_example_textarea_3();
  // lv_example_tileview_1();
  // lv_example_win_1();

  // Demos
  // Demos in benchmark/lv_demo_benchmark.h
  // Define LV_USE_DEMO_BENCHMARK in lib/lv_conf.h to use these demos
  // lv_demo_benchmark(LV_DEMO_BENCHMARK_MODE_RENDER_AND_DRIVER);
  // lv_demo_benchmark(LV_DEMO_BENCHMARK_MODE_REAL);
  // lv_demo_benchmark(LV_DEMO_BENCHMARK_MODE_RENDER_ONLY);
  // lv_demo_benchmark_run_scene(LV_DEMO_BENCHMARK_MODE_RENDER_AND_DRIVER, 0);

  // Demo in keypad_encoder/lv_demo_keypad_encoder.h
  // Define LV_USE_DEMO_KEYPAD_AND_ENCODER in lib/lv_conf.h to use this demo
  // lv_demo_keypad_encoder();

  // Demo in music/lv_demo_music.h
  // Define LV_USE_DEMO_MUSIC in lib/lv_conf.h to use this demo
  // lv_demo_music();

  // Demo in stress/lv_demo_stress.h
  // Define LV_USE_DEMO_STRESS in lib/lv_conf.h to use this demo
  // lv_demo_stress();

  // Demo in widgets/lv_demo_widgets.h
  // Define LV_USE_DEMO_WIDGETS in lib/lv_conf.h to use this demo
  // lv_demo_widgets();

  // Demo in flex_layout/lv_demo_flex_layout.h
  // Define LV_USE_DEMO_FLEX_LAYOUT and LV_USE_USER_DATA in lib/lv_conf.h to use this demo
  // lv_demo_flex_layout();
}

void loop() {
  lv_timer_handler();   // let the GUI do its work
  delay(5);
}
