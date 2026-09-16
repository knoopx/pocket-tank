/* persist_port_esp.c — progression ports on the device: NVS blob + wall clock.
 * Wall clock: esp time, set from the chip clock at boot (the 4B has no
 * external RTC); until it is set it is 0 on a cold boot, which simply
 * disables the ravenous rule. */
#include "progression.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "sdkconfig.h"

static const char *TAG = "persist";

bool persist_port_load(void *buf, size_t max, size_t *got) {
    nvs_handle_t h; if (nvs_open("tank", NVS_READONLY, &h) != ESP_OK) return false;
    size_t len = 0; esp_err_t e = nvs_get_blob(h, "save", NULL, &len);   /* the stored length first */
    if (e == ESP_OK && (len == 0 || len > max)) e = ESP_ERR_NVS_INVALID_LENGTH;   /* a newer build's save */
    if (e == ESP_OK) e = nvs_get_blob(h, "save", buf, &len);
    nvs_close(h);
    if (e == ESP_OK) *got = len;
    else if (e != ESP_ERR_NVS_NOT_FOUND) ESP_LOGW(TAG, "load failed: %s (%u bytes)", esp_err_to_name(e), (unsigned)len);
    return e == ESP_OK;
}
bool persist_port_save(const void *buf, size_t len) {
    nvs_handle_t h; if (nvs_open("tank", NVS_READWRITE, &h) != ESP_OK) return false;
    esp_err_t e = nvs_set_blob(h, "save", buf, len); if (e == ESP_OK) e = nvs_commit(h);
    nvs_close(h); if (e != ESP_OK) ESP_LOGW(TAG, "save failed: %s", esp_err_to_name(e));
    return e == ESP_OK;
}
/* the keeper's reset: the whole "tank" namespace goes - "save" and the
 * director's parked "bk" alike - so nothing can bring the old tank back */
bool persist_port_erase(void) {
    nvs_handle_t h; if (nvs_open("tank", NVS_READWRITE, &h) != ESP_OK) return false;
    esp_err_t e = nvs_erase_all(h); if (e == ESP_OK) e = nvs_commit(h);
    nvs_close(h);
    if (e != ESP_OK) ESP_LOGW(TAG, "erase failed: %s", esp_err_to_name(e));
    else ESP_LOGI(TAG, "every saved tank erased");
    return e == ESP_OK;
}
/* the 4B has no external RTC: the wall clock is the chip's time since boot
 * (esp_timer), read by progression_wake for "lived through" time */
int64_t clock_port_now_unix(void) { return esp_timer_get_time() / 1000000; }

