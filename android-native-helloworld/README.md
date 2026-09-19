# Hello Native (Android, NDK/C++)

Application Android 100% native : aucun code Java/Kotlin n'est nécessaire.
`android.app.NativeActivity` (fournie par le framework Android) charge
directement la librairie native `native-activity`, dont le point d'entrée
est `android_main()` dans `app/src/main/cpp/main.cpp`. Au démarrage, ce code
natif crée un `TextView` via JNI et l'affiche à l'écran avec le texte
« Hello, World! » (et le log logcat correspondant).

## Structure

```
android-native-helloworld/
├── CMakeLists.txt              # point d'entrée CMake (racine du projet)
├── CMakeSettings.json          # configurations Android pour Visual Studio
└── app/src/main/
    ├── AndroidManifest.xml     # déclare la NativeActivity
    └── cpp/
        ├── CMakeLists.txt      # build de la lib native + android_native_app_glue
        └── main.cpp            # logique native (android_main)
```

## Prérequis (Visual Studio)

Dans le Visual Studio Installer, installer le workload :
- **Développement mobile avec C++** (inclut le NDK Android, le SDK Android
  et l'OpenJDK nécessaires ; cocher les composants "Android NDK" et
  "Android SDK" si proposés individuellement).

## Ouvrir le projet

1. Visual Studio → **Fichier > Ouvrir > Dossier...** et sélectionner le
   dossier `android-native-helloworld`.
2. Visual Studio détecte automatiquement `CMakeLists.txt` et
   `CMakeSettings.json` et propose les configurations Android
   (`android-arm64-v8a-Debug`, etc.) dans la barre d'outils de
   configuration.
3. Choisir une configuration (ex. `android-arm64-v8a-Debug`), puis
   **Générer > Générer tout** (Ctrl+Maj+B).
4. Brancher un appareil Android (ou démarrer un émulateur), puis
   **Déboguer > Démarrer sans débogage** (Ctrl+F5) pour installer et
   lancer l'application. L'écran doit afficher « Hello, World! ».

## Build en ligne de commande (alternative)

Depuis une invite « x64 Native Tools » avec le NDK dans le `PATH` :

```powershell
cmake -G Ninja -B out/build/android-arm64-v8a-Debug ^
  -DCMAKE_TOOLCHAIN_FILE=%ANDROID_NDK%/build/cmake/android.toolchain.cmake ^
  -DANDROID_ABI=arm64-v8a -DANDROID_PLATFORM=android-21
cmake --build out/build/android-arm64-v8a-Debug
```
