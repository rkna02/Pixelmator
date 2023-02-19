/*
*  File:        filler.cpp
*  Description: Implementation of functions in the filler namespace.
*
*/

/*
*  Performs a flood fill using breadth first search.
*  LEVEL ORDER TRAVERSAL
*
*  PARAM:  config - FillerConfig struct to setup the fill
*  RETURN: animation object illustrating progression of flood fill algorithm
*/
animation filler::FillBFS(FillerConfig& config) {
  // complete your implementation below
  // You should replace the following line with a
  // correct call to fill.
  return Fill<Queue>(config);
}

/*
*  Performs a flood fill using depth first search.
*  PREORDER TRAVERSAL
*
*  PARAM:  config - FillerConfig struct to setup the fill
*  RETURN: animation object illustrating progression of flood fill algorithm
*/
animation filler::FillDFS(FillerConfig& config) {
  // complete your implementation below
  // You should replace the following line with a
  // correct call to fill.
  return Fill<Stack>(config);
}

/*
*  Run a flood fill on an image starting at the seed point
*
*  PARAM:  config - FillerConfig struct with data for flood fill of image
*  RETURN: animation object illustrating progression of flood fill algorithm
*/
template <template <class T> class OrderingStructure> animation filler::Fill(FillerConfig& config)
{
  /*
  * You need to implement this function!
  *
  * This is the basic description of a flood-fill algorithm: Every fill
  * algorithm requires an ordering structure, which is passed to this
  * function via its template parameter. For a breadth-first-search
  * fill, that structure is a Queue, for a depth-first-search, that
  * structure is a Stack. To begin the algorithm, you simply place the
  * given point in the ordering structure, marking it processed
  * (the way you mark it is a design decision you'll make yourself).
  * We have a choice to either change the color, if appropriate, when we
  * add the point to the OS, or when we take it off. In our test cases,
  * we have assumed that you will change the color when a point is added
  * to the structure.
  * Until the structure is empty, you do the following:
  *
  * 1.     Remove a point from the ordering structure, and then...
  *
  *        1.    add its unprocessed neighbors (up/down/left/right) whose color values are
  *              within (or equal to) tolerance distance from the center,
  *              to the ordering structure, and
  *              mark them as processed.
  *        2.    if it is an appropriate frame, send the current PNG to the
  *              animation (as described below).
  *
  * 2.     When implementing your breadth-first-search and
  *        depth-first-search fills, you will need to explore neighboring
  *        pixels (up/down/left/right) in some order.
  *
  *        While the order in which you examine neighbors does not matter
  *        for a proper fill, you must use the same order as we do for
  *        your animations to come out like ours! The order you should put
  *        neighboring pixels **ONTO** the queue or stack is based on the
  *        following priority condition:
  *        ** MINIMUM COLOR DISTANCE FROM THE CURRENT PIXEL **
  *        Ties are broken first by minimum y-coordinate, then by minimum x-coordinate.
  *        The HSLAPixel.dist() function will be useful, and you should
  *        take advantage of the functionality in your PriorityNeighbours class.
  * 
  *        If you process the neighbours in a different order, your fill may
  *        still work correctly, but your animations will be different
  *        from the grading scripts!
  *
  * 3.     For every k pixels filled, **starting at the kth pixel**, you
  *        must add a frame to the animation, where k = frameFreq.
  *
  *        For example, if frameFreq is 4, then after the 4th pixel has
  *        been filled you should add a frame to the animation, then again
  *        after the 8th pixel, etc.  You must only add frames for the
  *        number of pixels that have been filled, not the number that
  *        have been checked. So if frameFreq is set to 1, a pixel should
  *        be filled every frame.
  *
  * 4.     Finally, as you leave the function, send one last frame to the
  *        animation. This frame will be the final result of the fill, and
  *        it will be the one we test against.
  *
  */

  // complete your implementation below
  // HINT: you will likely want to declare some kind of structure to track
  //       which pixels have already been visited

  int framecount = 0; // increment after processing one pixel; used for producing animation frames (step 3 above)
  animation anim;  // final animation object to be completed, more information can be found in animation.h and animation.cpp
  OrderingStructure<PixelPoint> os;  // stack/queue
  vector<vector<bool>> processed(config.img.width(), vector<bool>(config.img.height(), false));  // 2D vector to keep track of processed/unprocessed pixels
  HSLAPixel newpixel;
  HSLAPixel *oldpixel;
  PixelPoint point;
  //double distance = config.seedpoint.color.dist(config.seedpoint.color);

  //cout << config.img.width() << " " << config.img.height() << endl;
  //cout << processed[149][148] << endl;
  
  //cout << config.img.width() << " " << config.img.height() << endl;
  // add root pixel 
  os.Add(config.seedpoint);

  // keep looping until ordering structure is empty
  while (!os.IsEmpty()) {
    point = os.Remove();  // remove point from ordering structure

    // determine priority neighbours 
    config.neighbourorder.SetReferenceColor(point.color);
    if (point.x > 0 ) {
      PixelPoint pt(point.x - 1, point.y, *(config.img.getPixel(point.x - 1, point.y)));
      //cout << "first" << endl;
      //cout << point.x - 1 << " " << point.y << endl;
      //cout << "distance: " << abs(pt.color.dist(config.seedpoint.color)) << endl;
      //cout << config.tolerance << endl;
      if (!processed[point.x - 1][point.y] && (abs(pt.color.dist(config.seedpoint.color)) <= config.tolerance)) {
        config.neighbourorder.Insert(pt);
      }
    } 
    if (point.x < config.img.width() - 1) {
      PixelPoint pt(point.x + 1, point.y, *(config.img.getPixel(point.x + 1, point.y)));
      //cout << "second" << endl;
      //cout << point.x + 1 << " " << point.y << endl
      //cout << "distance: " << abs(pt.color.dist(config.seedpoint.color)) << endl;
      //cout << config.tolerance << endl;
      if (!processed[point.x + 1][point.y] && (abs(pt.color.dist(config.seedpoint.color)) <= config.tolerance)) {
        config.neighbourorder.Insert(pt);
      }
    }
    if (point.y > 0) {
      PixelPoint pt(point.x, point.y - 1, *(config.img.getPixel(point.x, point.y - 1)));
      //cout << "third" << endl;
      //cout << point.x << " " << point.y - 1 << endl;
      //cout << "distance: " << abs(pt.color.dist(config.seedpoint.color)) << endl;
      //cout << config.tolerance << endl;
      if (!processed[point.x][point.y - 1] && (abs(pt.color.dist(config.seedpoint.color)) <= config.tolerance)) {
        config.neighbourorder.Insert(pt);
      }
    }
    if (point.y < config.img.height() - 1) {
      PixelPoint pt(point.x, point.y + 1, *(config.img.getPixel(point.x, point.y + 1)));
      //cout << "fourth" << endl;
      //cout << point.x << " " << point.y + 1 << endl;
      //cout << "distance: " << abs(pt.color.dist(config.seedpoint.color)) << endl;
      //cout << config.tolerance << endl;
      if (!processed[point.x][point.y + 1] && (abs(pt.color.dist(config.seedpoint.color)) <= config.tolerance)) {
        config.neighbourorder.Insert(pt);
      }
    }

    // push unprocessed neighbours to the ordering structure in order 
    while (!config.neighbourorder.IsEmpty()) {
      PixelPoint point_new = config.neighbourorder.Remove();
      os.Add(point_new);
      processed[point_new.x][point_new.y] = true;  // mark is as processed

      // Determine the pixel color and update image pixel 
      newpixel = (*config.picker)(point_new);
      oldpixel = config.img.getPixel(point_new.x, point_new.y);
      oldpixel->h = newpixel.h;
      oldpixel->s = newpixel.s;
      oldpixel->l = newpixel.l;
      oldpixel->a = newpixel.a;

      // update frame count after filling pixel with color
      framecount++;

      // add frame to animation if appropriate
      if (framecount % config.frameFreq == 0) {
        anim.addFrame(config.img);
      }

    }
  
  }
  
  // add one last frame before ending function
  anim.addFrame(config.img);

  return anim;
}
