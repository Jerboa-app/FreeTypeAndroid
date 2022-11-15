package app.jerboa.freetypeandroid

import android.content.res.AssetManager

class FreeTypeWrapper {
    companion object {
        init {
            System.loadLibrary("TextRenderer")
        }
    }

    external fun assetManager(
        assets: AssetManager
    )

    external fun TextRenderer(resX: Float, resY: Float)

    external fun renderText(
        text: String,
        x: Float,
        y: Float,
        scale: Float,
        r: Float,
        g: Float,
        b: Float
    )

    external fun free()
}