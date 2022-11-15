package app.jerboa.freetypeandroid.ui.view

import android.content.res.AssetManager
import android.opengl.GLES30.*
import android.opengl.GLSurfaceView
import android.opengl.Matrix
import android.util.Log
import app.jerboa.freetypeandroid.utils.glBufferStatus
import app.jerboa.freetypeandroid.utils.glError
import app.jerboa.freetypeandroid.FreeTypeWrapper
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10
import kotlin.math.ln
import kotlin.random.Random

class GLRenderer (
    private val resolution: Pair<Int,Int>,
    private val assets: AssetManager
    ) : GLSurfaceView.Renderer {

    private val projection: FloatArray = FloatArray(16){0f}
    private val invProjection: FloatArray = FloatArray(16){0f}

    private val wrapper = FreeTypeWrapper()

    private var posX: Double = resolution.first/2.0
    private var posY: Double = resolution.second/2.0

    private var lastTime = System.nanoTime()

    init {
        Matrix.orthoM(projection,0,0f,resolution.first.toFloat(),0f,resolution.second.toFloat(),0.0f,100f)
        Matrix.invertM(invProjection,0,projection,0)
    }

    fun nextGaussian(): Double {
        val u = kotlin.random.Random.nextDouble()
        return ln(u/(1.0-u)) *0.6266570686577501
    }


    override fun onSurfaceCreated(p0: GL10?, p1: EGLConfig?) {

        val vers = IntArray(2)
        glGetIntegerv(GL_MAJOR_VERSION, vers, 0)
        glGetIntegerv(GL_MINOR_VERSION, vers, 1)
        Log.d("glVersion","${vers[0]}, ${vers[1]}")

        glPixelStorei(GL_UNPACK_ALIGNMENT,1)
        wrapper.assetManager(assets)
        wrapper.TextRenderer(resolution.first.toFloat(),resolution.second.toFloat())
    }

    override fun onSurfaceChanged(p0: GL10?, p1: Int, p2: Int) {
        glViewport(0,0,p1,p2)
    }

    override fun onDrawFrame(p0: GL10?) {

        glClearColor(1f,1f,1f,1f)
        glViewport(0,0,resolution.first,resolution.second)
        glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT)

        glBindFramebuffer(GL_FRAMEBUFFER,0)

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        wrapper.renderText(
            "Hello Android\nNDK!",
            posX.toFloat(),posY.toFloat(),
            0.5f,
            0f,
            0f,
            0f
        )

        val time = System.nanoTime()
        val delta = time - lastTime
        lastTime = time

        val dt = delta * 1e-9
        posX += 100.0*nextGaussian()*dt
        posY += 100.0*nextGaussian()*dt

        val dx = posX - resolution.first/2.0
        val dy = posY - resolution.second/2.0

        if (dx*dx+dy*dy > 200.0*200.0) {
            posX -= dx*dt
            posY -= dy*dt
        }

        glError()
        glBufferStatus()
    }

}