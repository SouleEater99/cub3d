Your name and email address were configured automatically based
on your username and hostname. Please check that they are accurate.
You can suppress this message by setting them explicitly. Run the
following command and follow the instructions in your editor to edit
your configuration file:

    git config --global --edit

After doing this, you may fix the identity used for this commit with:

    git commit --amend --reset-author

 4 files changed, 215 insertions(+), 70 deletions(-)
 create mode 100644 .vscode/settings.json
 rewrite mandatory/maps/invalid_map2.cub (100%)
Enumerating objects: 17, done.
Counting objects: 100% (17/17), done.
Delta compression using up to 20 threads
Compressing objects: 100% (9/9), done.
Writing objects: 100% (10/10), 2.17 KiB | 2.17 MiB/s, done.
Total 10 (delta 5), reused 0 (delta 0), pack-reused 0
remote: Resolving deltas: 100% (5/5), completed with 5 local objects.
To github.com:SouleEater99/cub3d.git
   ede7d14..226e24b  aziz -> aziz

# Ryacasting:

- `x`: Iterator for the screen's columns.
- `perp_wall_dist`: Stores the perpendicular distance to the wall.
- `hit`: Flag to indicate when a wall is hit.
- `side`: Indicates if the wall hit was on the X-axis (0) or Y-axis (1).
- `color`: Holds the color for the wall slice based on the side.
- `line_height`: Height of the wall slice to render.
- `draw_start` and draw_end: The start and end points for drawing a wall slice.

### What `delta_dist_x` and `delta_dist_y` Represent?

- `delta_dist_x` and `delta_dist_y` represent the normalized distances a ray needs to travel along the X-axis and Y-axis, respectively, in order to cross a single grid cell.

- `delta_dist_x`: The distance along the ray's direction needed to move from one vertical grid line to the next.
- `delta_dist_y`: The distance along the ray's direction needed to move from one horizontal grid line to the next.

These values depend on the angle of the ray:

- If the ray is almost horizontal (close to the X-axis), `delta_dist_x` will be relatively small (since it needs less distance to hit the next vertical line) and `delta_dist_y` will be relatively large (since it takes a lot of travel along the ray to reach the next horizontal line).
- Conversely, if the ray is almost vertical (close to the Y-axis), `delta_dist_y` will be small, and `delta_dist_x` will be large.

