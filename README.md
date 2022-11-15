### Minimum Working Example of FreeType rendering with Android Jetpack compose

#### Outline 

- The [cpp folder](https://github.com/Jerboa-app/FreeTypeAndroid/tree/main/app/src/main/cpp) contains basic TextRenderer and Type objects for handling 
  rendering (and loading freetpye) and storing a typeface respectively.
- A (Java JNI) Kotlin interface is defined in [main.cpp](https://github.com/Jerboa-app/FreeTypeAndroid/blob/main/app/src/main/cpp/main.cpp)
- The Kotlin counterpart for the interface is [here](https://github.com/Jerboa-app/FreeTypeAndroid/blob/main/app/src/main/java/app/jerboa/freetypeandroid/FreeTypeWrapper.kt)
- To use a different custom font, place it in the [assets/fonts folder](https://github.com/Jerboa-app/FreeTypeAndroid/tree/main/app/src/main/assets/fonts)
- The main render loop occurs as part of a [GLSurfaceView](https://github.com/Jerboa-app/FreeTypeAndroid/blob/main/app/src/main/java/app/jerboa/freetypeandroid/ui/view/GLRenderer.kt) setup
- The app runs by an [activity](https://github.com/Jerboa-app/FreeTypeAndroid/blob/main/app/src/main/java/app/jerboa/freetypeandroid/MainActivity.kt), launching a simple [compose function](https://github.com/Jerboa-app/FreeTypeAndroid/blob/main/app/src/main/java/app/jerboa/freetypeandroid/composeable/Example.kt)

##### Tested on 

- LGE Nexus 5 Physical device (Android 6.0.1)
- Sony J8110 (Xperia 1, OG) Physical device (Android 11)

#### Running

All is included, openning as an Android studio project should allow for a straightforward compilation

FreeType2 is vendored with the code [README](https://github.com/Jerboa-app/FreeTypeAndroid/blob/main/app/src/main/cpp/include/freetype/README), the CMakeLists.txt could be edited to use some extant version.

![example](https://github.com/Jerboa-app/FreeTypeAndroid/blob/main/example.gif)

