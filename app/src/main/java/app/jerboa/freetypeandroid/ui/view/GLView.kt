package app.jerboa.freetypeandroid.ui.view

import android.content.Context
import android.content.res.AssetManager
import android.graphics.PixelFormat
import android.opengl.GLSurfaceView
import android.util.AttributeSet
import android.util.Log
import app.jerboa.freetypeandroid.ui.view.GLRenderer
import javax.microedition.khronos.egl.EGL10


class GLView (
    context: Context,
    attr: AttributeSet? = null,
    private val resolution: Pair<Int,Int>,
    private val assets: AssetManager
    ) :
    GLSurfaceView(context,attr)
{

    private val renderer = GLRenderer(resolution,assets)

    internal class ConfigChooser : EGLConfigChooser {
        override fun chooseConfig(
            egl: EGL10?,
            display: javax.microedition.khronos.egl.EGLDisplay?
        ): javax.microedition.khronos.egl.EGLConfig? {
            val attribs = intArrayOf(
                EGL10.EGL_LEVEL, 0,
                EGL10.EGL_RENDERABLE_TYPE, 64,  // EGL_OPENGL_ES3_BIT
                EGL10.EGL_SAMPLES, 0,  //
                EGL10.EGL_BLUE_SIZE, 8,
                EGL10.EGL_GREEN_SIZE, 8,
                EGL10.EGL_RED_SIZE, 8,
                EGL10.EGL_ALPHA_SIZE, 8,
                EGL10.EGL_NONE
            )
            val configs: Array<javax.microedition.khronos.egl.EGLConfig?> = arrayOfNulls<javax.microedition.khronos.egl.EGLConfig>(1)
            val configCounts = IntArray(1)

            egl!!.eglChooseConfig(display, attribs, configs, 1, configCounts)
            return if (configCounts[0] == 0) {
                Log.d("configChooser","no configs")
                // Failed! Error handling.
                val attribs = intArrayOf(
                    EGL10.EGL_RENDERABLE_TYPE, 64,  // EGL_OPENGL_ES3_BIT
                    EGL10.EGL_BLUE_SIZE, 8,
                    EGL10.EGL_GREEN_SIZE, 8,
                    EGL10.EGL_RED_SIZE, 8,
                    EGL10.EGL_ALPHA_SIZE, 8,
                    EGL10.EGL_NONE
                )
                val configs: Array<javax.microedition.khronos.egl.EGLConfig?> = arrayOfNulls<javax.microedition.khronos.egl.EGLConfig>(1)
                val configCounts = IntArray(1)

                egl!!.eglChooseConfig(display, attribs, configs, 1, configCounts)
                return configs[0]
            } else {
                configs[0]
            }
        }
    }

    init {
        setEGLContextClientVersion(3)
        preserveEGLContextOnPause = true
        //setEGLConfigChooser(ConfigChooser())
        setEGLConfigChooser(8, 8, 8, 8, 16, 0)
        holder.setFormat(PixelFormat.RGBA_8888)
        setRenderer(renderer)
    }

}