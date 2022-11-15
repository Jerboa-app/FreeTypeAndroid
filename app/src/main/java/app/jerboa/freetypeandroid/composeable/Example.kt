package app.jerboa.freetypeandroid.composeable

import android.content.res.AssetManager
import androidx.compose.runtime.Composable
import androidx.compose.ui.viewinterop.AndroidView
import app.jerboa.freetypeandroid.ui.view.GLView

@Composable
fun Example(resolution: Pair<Int,Int>, assets: AssetManager){
    AndroidView(
        factory = {
            GLView(
                it, null,
                resolution,
                assets
            )
        },
        update = { view ->
            //null
        }
    )
}