## [Original README](https://github.com/shaka-project/shaka-packager#readme)

## Changes:
  - Progress bar, works with both sidx box and filesize (slightly less accurate) variants.
    <br>
    Example: ![bar](https://i2.lensdump.com/i/tJ4m7q.png)
  - [Applies to ATVP & iTunes]. Defined a new FourCC type `clcp`, which is what Apple uses for Closed Captions. Since shaka doesn't support it, when found it's simply sent to devlog and safely ignored instead of throwing an annoying NotImplemented warning that could also be concerning as the user has no idea whether the sample skipped was actually important to video integrity and such.
  - Warnings such as timestamp adjustment due to a missing EditList are no longer printed on the console as those adjustments work perfectly already.
  - Added newlines to some log messages to make things a little prettier. 