## [Original README](https://github.com/shaka-project/shaka-packager#readme)

## Changes:
  - Progress bar, works with both sidx box and filesize (slightly less accurate) variants.
    <br>
    Example: ![bar](https://i1.lensdump.com/i/tJSyJM.png)
  - [Applies to ATVP & iTunes]. Defined a new FourCC type `clcp`, which is what Apple uses for Closed Captions. Since shaka doesn't support it, when found it's simply sent to devlog and safely ignored instead of throwing an annoying NotImplemented warning that could also be concerning as the user has no idea whether the sample skipped was actually important to video integrity and such.
  - Warnings such as timestamp adjustment due to a missing EditList are no longer printed on the console as those adjustments work perfectly already.
  - Added newlines to some log messages to make things a little prettier.

## Issues:
  - The ■ character used in the progress bar will be displayed incorrectly in shells that don't support unicode. In that case grab the uglier, but functional version that uses printable ASCII from Releases. Example:
![ascii](https://i1.lensdump.com/i/tJScI0.png)
  - Doesn't work as intended as a standalone executable (results in dozens of progress bars being generated each on a new line). Likely because of using `if` instead of `while` in the relevant functions. It is that way because based on my tests the latter wouldn't work properly on Linux. The intended use is inside vt which runs it with subprocess.run, and that works perfectly on either OS, so I'm not going to attempt to fix this part further. If someone manages to get it working properly for all cases, please submit a PR.
