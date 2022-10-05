// HASH COLLISIONS: YES
// timestamp: 1.662183041E12

package main;

import com.area9innovation.flow.*;

@SuppressWarnings("unchecked")
final public class Module_target {
	public static Object[] g_allTargets;
	public static Reference<String> g_browser;
	public static Reference<String> g_deviceType;
	public static Reference<String> g_flashVersion;
	public static Reference<Boolean> g_isAndroid;
	public static Reference<Boolean> g_isIos;
	public static Reference<Boolean> g_isLinux;
	public static Reference<Boolean> g_isMacOSX;
	public static Reference<Boolean> g_isWindows;
	public static Reference<String> g_majorOsPart;
	public static Reference<String> g_minorOsPart;
	public static Reference<String> g_resolution;
	public static Reference<String> g_userAgent;
	public static int g_screenDPI;
	public static double g_screenDensity;
	public static boolean g_cgi;
	public static boolean g_cpp;
	public static boolean g_js;
	public static boolean g_mobile;
	public static boolean g_neko;
	public static boolean g_nogui;
	public static boolean g_safariBrowser;
	public static int g_bootTargetInit;
	public static void init_bootTargetInit() {
		if (Module_devmode.f_isDevMode()) {
			Module_runtime.f_println(("target: "+Native.getTargetName()));
			Module_runtime.f_println("target: ");
			Module_runtime.f_println(("target: windows="+((Func1<String,Boolean>)(Func1)Wrappers.w_toString).invoke(((Boolean)Module_target.f_windows()))));
			Module_runtime.f_println(("target: windowsxp="+((Func1<String,Boolean>)(Func1)Wrappers.w_toString).invoke(((Boolean)Module_target.f_windowsxp()))));
			Module_runtime.f_println(("target: macosx="+((Func1<String,Boolean>)(Func1)Wrappers.w_toString).invoke(((Boolean)Module_target.f_macosx()))));
			Module_runtime.f_println(("target: linux="+((Func1<String,Boolean>)(Func1)Wrappers.w_toString).invoke(((Boolean)Module_target.f_linux()))));
			Module_runtime.f_println(("target: ios="+((Func1<String,Boolean>)(Func1)Wrappers.w_toString).invoke(((Boolean)Module_target.f_ios()))));
			Module_runtime.f_println(("target: android="+((Func1<String,Boolean>)(Func1)Wrappers.w_toString).invoke(((Boolean)Module_target.f_android()))));
			Module_runtime.f_println("target: ");
			Module_runtime.f_println(("target: mobile="+((Func1<String,Boolean>)(Func1)Wrappers.w_toString).invoke(((Boolean)Module_target.g_mobile))));
			Module_runtime.f_println(("target: screenDPI="+((Func1<String,Integer>)(Func1)Wrappers.w_toString).invoke(((Integer)Module_target.g_screenDPI))));
			Module_runtime.f_println(("target: getOsFlow="+((Func1<String,String>)(Func1)Wrappers.w_toString).invoke(Module_target.f_getOsFlow())));
			Module_runtime.f_println(("target: getFlashVersion="+((Func1<String,String>)(Func1)Wrappers.w_toString).invoke(Module_target.f_getFlashVersion())));
			Module_runtime.f_println(("target: getBrowser="+((Func1<String,String>)(Func1)Wrappers.w_toString).invoke(Module_target.f_getBrowser())));
			Module_runtime.f_println(("target: getResolution="+((Func1<String,String>)(Func1)Wrappers.w_toString).invoke(Module_target.f_getResolution())));
			Module_runtime.f_println(("target: getUserAgent="+((Func1<String,String>)(Func1)Wrappers.w_toString).invoke(Module_target.f_getUserAgent())));
		} else {
		}
		g_bootTargetInit=0;
	}
	public static void init() {
		g_allTargets=Module_string.f_strSplit(Native.getTargetName(), ",");
		g_browser=((Reference<String>)(new Reference("")));
		g_deviceType=((Reference<String>)(new Reference("")));
		g_flashVersion=((Reference<String>)(new Reference("")));
		g_isAndroid=((Reference<Boolean>)(new Reference(false)));
		g_isIos=((Reference<Boolean>)(new Reference(false)));
		g_isLinux=((Reference<Boolean>)(new Reference(false)));
		g_isMacOSX=((Reference<Boolean>)(new Reference(false)));
		g_isWindows=((Reference<Boolean>)(new Reference(false)));
		g_majorOsPart=((Reference<String>)(new Reference("")));
		g_minorOsPart=((Reference<String>)(new Reference("")));
		g_resolution=((Reference<String>)(new Reference("")));
		g_userAgent=((Reference<String>)(new Reference("")));
		final Func1<Boolean,String> l1_$0 = (Func1<Boolean, String>)(String av) -> {
			return ((Boolean)Module_string.f_startsWith(av, "dpi="));
		};
		final Struct l2_gsymswitch0 = Module_array.f_find(Module_target.g_allTargets, ((Func1<Boolean,Object>)(Func1)l1_$0));
		Struct l3__tmp = l2_gsymswitch0;
		switch (l3__tmp.getTypeId()) {
		case 39/*None*/: {
			g_screenDPI=90;
			break;
		}
		case 103/*Some*/: {
			final Struct_Some l4__tmp = (Struct_Some)l3__tmp;
			final Object l5_v = l4__tmp.f_value;
			final String l6_v = ((String)l4__tmp.f_value);
			g_screenDPI=Module_math.f_s2i(Module_string.f_strRight(l6_v, 4));
			break;
		}
		default:
			throw new RuntimeException("Unexpected struct in switch: "+l3__tmp.getTypeName());
		}
		final Func1<Boolean,String> l8_$7 = (Func1<Boolean, String>)(String av) -> {
			return ((Boolean)Module_string.f_startsWith(av, "density="));
		};
		final Struct l9_gsymswitch1 = Module_array.f_find(Module_target.g_allTargets, ((Func1<Boolean,Object>)(Func1)l8_$7));
		Struct l10__tmp = l9_gsymswitch1;
		switch (l10__tmp.getTypeId()) {
		case 39/*None*/: {
			g_screenDensity=1.0;
			break;
		}
		case 103/*Some*/: {
			final Struct_Some l11__tmp = (Struct_Some)l10__tmp;
			final Object l12_v = l11__tmp.f_value;
			final String l13_v = ((String)l11__tmp.f_value);
			final double l14_parsedValue = Module_math.f_s2d(Module_string.f_strRight(l13_v, 8));
			if (Module_math.f_equalDoubles(l14_parsedValue, 0.0)) {
				g_screenDensity=1.0;
			} else {
				g_screenDensity=l14_parsedValue;
			}
			break;
		}
		default:
			throw new RuntimeException("Unexpected struct in switch: "+l10__tmp.getTypeName());
		}
		g_cgi=Module_target.f_hasTargetName("cgi");
		g_cpp=Module_target.f_hasTargetName("c++");
		g_js=Module_target.f_hasTargetName("js");
		g_mobile=(Module_target.f_hasTargetName("mobile")||Module_url_parameter.f_isUrlParameterTrue("overridemobile"));
		g_neko=Module_target.f_hasTargetName("neko");
		g_nogui=(((Module_target.g_neko||Module_target.g_cgi)||(Module_target.g_cpp&&!Module_target.f_hasTargetName("gui")))||(!(Module_url_parameter.f_getUrlParameter("nogui")).equals("")));
		g_safariBrowser=(Module_target.g_js&&Module_string.f_strContains(Native.toLowerCase(Module_target.f_getBrowser()), "safari"));
		init_bootTargetInit();
	}
	public static final boolean f_android() {
			Module_target.f_initOsParts();
			return ((boolean)Module_target.g_isAndroid.value);
		}
	public static final String f_getBrowser() {
			Module_target.f_initOsParts();
			return Module_target.g_browser.value;
		}
	public static final String f_getFlashVersion() {
			Module_target.f_initOsParts();
			return Module_target.g_flashVersion.value;
		}
	public static final String f_getOsFlow() {
			Module_target.f_initOsParts();
			return ((Module_target.g_majorOsPart.value+" ")+Module_target.g_minorOsPart.value);
		}
	public static final String f_getResolution() {
			Module_target.f_initOsParts();
			return Module_target.g_resolution.value;
		}
	public static final String f_getUserAgent() {
			Module_target.f_initOsParts();
			return Module_target.g_userAgent.value;
		}
	public static final boolean f_hasTargetName(String as) {
			return Module_array.f_contains(Module_target.g_allTargets, as);
		}
	public static final Object f_initOsParts() {
			if ((Module_target.g_majorOsPart.value).equals("")) {
				final Object l0_browserOs = Native.hostCall("getOs", SingletonStructs.arr_empty);
				Object l1_os;
				if ((!(Wrappers.w_toString.invoke(l0_browserOs)).equals("{}"))) {
					l1_os=l0_browserOs;
				} else {
					if (Module_target.f_hasTargetName("iOS")) {
						l1_os="iOS";
					} else {
						if (Module_target.f_hasTargetName("android")) {
							l1_os="Android";
						} else {
							if (Module_target.f_hasTargetName("windows")) {
								l1_os="Windows";
							} else {
								if (Module_target.f_hasTargetName("linux")) {
									l1_os="Linux";
								} else {
									if (Module_target.f_hasTargetName("macosx")) {
										l1_os="MacOSX";
									} else {
										l1_os="";
									}
								}
							}
						}
					}
				}
				final Object[] l2_osParts = Module_string.f_strSplit(((String)l1_os), ",");
				Module_target.g_majorOsPart.value = (((Native.length(l2_osParts)>0)&&(!(((String)(l2_osParts[0]))).equals("")))?((String)(l2_osParts[0])):"other");
				Module_target.g_minorOsPart.value = (((Native.length(l2_osParts)>1)&&(!(((String)(l2_osParts[1]))).equals("")))?((String)(l2_osParts[1])):"other");
				Module_target.g_isWindows.value = (Module_target.g_majorOsPart.value).equals("Windows");
				final Object l3_userAgentCheck = Native.hostCall("getUserAgent", SingletonStructs.arr_empty);
				((Reference<Object>)(Reference)Module_target.g_userAgent).value = ((!(Wrappers.w_toString.invoke(l3_userAgentCheck)).equals("{}"))?l3_userAgentCheck:"other");
				Module_target.g_isMacOSX.value = ((Boolean)((Module_target.g_majorOsPart.value).equals("MacOSX")||Module_string.f_strContains(Native.toLowerCase(Module_target.g_userAgent.value), "mac os x")));
				Module_target.g_isLinux.value = ((Boolean)((Module_target.g_majorOsPart.value).equals("Linux")||Module_string.f_strContains(Native.toLowerCase(Module_target.g_userAgent.value), "linux")));
				Module_target.g_isIos.value = (Module_target.g_majorOsPart.value).equals("iOS");
				Module_target.g_isAndroid.value = (Module_target.g_majorOsPart.value).equals("Android");
				final Object l4_flashCheck = Native.hostCall("getVersion", SingletonStructs.arr_empty);
				((Reference<Object>)(Reference)Module_target.g_flashVersion).value = ((!(Wrappers.w_toString.invoke(l4_flashCheck)).equals("{}"))?l4_flashCheck:"other");
				final Object l5_browserCheck = Native.hostCall("getBrowser", SingletonStructs.arr_empty);
				((Reference<Object>)(Reference)Module_target.g_browser).value = ((!(Wrappers.w_toString.invoke(l5_browserCheck)).equals("{}"))?l5_browserCheck:"other");
				final Object l6_resolutionCheck = Native.hostCall("getResolution", SingletonStructs.arr_empty);
				((Reference<Object>)(Reference)Module_target.g_resolution).value = ((!(Wrappers.w_toString.invoke(l6_resolutionCheck)).equals("{}"))?l6_resolutionCheck:"other");
				final Object l7_deviceTypeCheck = Native.hostCall("getDeviceType", SingletonStructs.arr_empty);
				((Reference<Object>)(Reference)Module_target.g_deviceType).value = ((!(Wrappers.w_toString.invoke(l7_deviceTypeCheck)).equals("{}"))?l7_deviceTypeCheck:"other");
				return null;
			} else {
				return null;
			}
		}
	public static final boolean f_ios() {
			Module_target.f_initOsParts();
			return ((boolean)Module_target.g_isIos.value);
		}
	public static final boolean f_linux() {
			Module_target.f_initOsParts();
			return ((boolean)Module_target.g_isLinux.value);
		}
	public static final boolean f_macosx() {
			Module_target.f_initOsParts();
			return ((boolean)Module_target.g_isMacOSX.value);
		}
	public static final boolean f_windows() {
			Module_target.f_initOsParts();
			return ((boolean)Module_target.g_isWindows.value);
		}
	public static final boolean f_windowsxp() {
			final String l0_ua = Native.toLowerCase(Module_target.f_getUserAgent());
			return (Module_string.f_strContains(l0_ua, "windows nt 5.1")||Module_string.f_strContains(l0_ua, "windows xp"));
		}
}
