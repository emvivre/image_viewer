# image_viewer
Simple portable viewer in SDL. Allow to display an image in an arbitrary resoution, without applying any smoothing filter on the pixels. This reveals to be interesting in order to display very small images.

The resolution specify by constant variable (see ``main.cpp``):

```
static const int MAX_SCREEN_WIDTH = 1360;
static const int MAX_SCREEN_HEIGHT = 768;
```

To display an image:
```
$ ./image_viewer <YOUR_IMAGE>
```

Type ``ESCAPE`` or ``q`` to quit the program.