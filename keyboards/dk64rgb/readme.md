# DKKB DK64RGB

- Keyboard Maintainer: [Yaroslav Chvanov](https://github.com/Yaroslav Chvanov)
- Hardware Availability: _Links to where you can find this hardware_

Make example for this keyboard (after setting up your build environment):

    make dk64rgb:default

Flashing example for this keyboard:

    make dk64rgb:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

See https://sr.ht/~showy_fence/dk64rgb-everything for some more details.

## Bootloader

Enter the bootloader:

- **Keycode in layout**: Press the key mapped to `QK_BOOT`. You can map it in Vial on the stock firmware.
- **Bootmagic reset**: With this firmware, hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard.

## Unusable last row

This uses the A9 pin which is discouraged by QMK (<https://docs.qmk.fm/platformdev_blackpill_f4x1#pins-to-be-avoided>) and apparently isn't supported by ChibiOS.
Patch ChibiOS like this, based on [[keyboards/xelus/valor_frl_tkl/rev2_0/readme.md]].
Otherwise the rightmost row will randomly work with a delay or even introduce ghosting on other keys.

```diff
diff --git a/os/hal/ports/STM32/LLD/OTGv1/hal_usb_lld.c b/os/hal/ports/STM32/LLD/OTGv1/hal_usb_lld.c
index 1d2611af..4f0feb86 100644
--- a/os/hal/ports/STM32/LLD/OTGv1/hal_usb_lld.c
+++ b/os/hal/ports/STM32/LLD/OTGv1/hal_usb_lld.c
@@ -55,15 +55,14 @@
 #if defined(BOARD_OTG_NOVBUSSENS)
 #define GCCFG_INIT_VALUE        (GCCFG_NOVBUSSENS | GCCFG_PWRDWN)
 #else
-#define GCCFG_INIT_VALUE        (GCCFG_VBUSASEN | GCCFG_VBUSBSEN |          \
-                                 GCCFG_PWRDWN)
+#define GCCFG_INIT_VALUE        (GCCFG_NOVBUSSENS | GCCFG_PWRDWN)
 #endif

 #elif STM32_OTG_STEPPING == 2
 #if defined(BOARD_OTG_NOVBUSSENS)
-#define GCCFG_INIT_VALUE        GCCFG_PWRDWN
+#define GCCFG_INIT_VALUE        (GCCFG_NOVBUSSENS | GCCFG_PWRDWN)
 #else
-#define GCCFG_INIT_VALUE        (GCCFG_VBDEN | GCCFG_PWRDWN)
+#define GCCFG_INIT_VALUE        (GCCFG_NOVBUSSENS | GCCFG_VBDEN | GCCFG_PWRDWN)
 #endif

 #endif
@@ -871,7 +870,7 @@ void usb_lld_start(USBDriver *usbp) {
     otgp->PCGCCTL = 0;

     /* VBUS sensing and transceiver enabled.*/
-    otgp->GOTGCTL = GOTGCTL_BVALOEN | GOTGCTL_BVALOVAL;
+    // otgp->GOTGCTL = GOTGCTL_BVALOEN | GOTGCTL_BVALOVAL;

 #if defined(BOARD_OTG2_USES_ULPI)
 #if STM32_USB_USE_OTG1
diff --git a/os/hal/ports/STM32/LLD/OTGv1/hal_usb_lld.h b/os/hal/ports/STM32/LLD/OTGv1/hal_usb_lld.h
index e46c03f9..1409d1d3 100644
--- a/os/hal/ports/STM32/LLD/OTGv1/hal_usb_lld.h
+++ b/os/hal/ports/STM32/LLD/OTGv1/hal_usb_lld.h
@@ -534,7 +534,7 @@ struct USBDriver {
  * @notapi
  */
 #if (STM32_OTG_STEPPING == 1) || defined(__DOXYGEN__)
-#define usb_lld_connect_bus(usbp) ((usbp)->otg->GCCFG |= GCCFG_VBUSBSEN)
+#define usb_lld_connect_bus(usbp)
 #else
 #define usb_lld_connect_bus(usbp) ((usbp)->otg->DCTL &= ~DCTL_SDIS)
 #endif
@@ -545,7 +545,7 @@ struct USBDriver {
  * @notapi
  */
 #if (STM32_OTG_STEPPING == 1) || defined(__DOXYGEN__)
-#define usb_lld_disconnect_bus(usbp) ((usbp)->otg->GCCFG &= ~GCCFG_VBUSBSEN)
+#define usb_lld_disconnect_bus(usbp)
 #else
 #define usb_lld_disconnect_bus(usbp) ((usbp)->otg->DCTL |= DCTL_SDIS)
 #endif
```
