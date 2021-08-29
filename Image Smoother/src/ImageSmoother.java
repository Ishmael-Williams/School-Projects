import java.awt.Color;
import java.awt.image.*;
import java.io.File;
import java.io.IOException;
import java.util.Arrays;

import javax.imageio.ImageIO;

/*The main function takes an image and reduces noise through  
 * one of two filters: image averaging or median filter,
 * based upon the filter type indicated at the beginning of the function.
*/
public class ImageSmoother {
	public static void main(String[] args) throws IOException {
		// Median filter used for filterType = 1, and average filter for filterType = 2
		int filterType = 1;
		String path = null;

		/*Get the image and set variables*/
		// Read image
		BufferedImage fighterBI = null;
		File fighterPicture = new File("Images/fighter_noise_5.jpg");
		fighterBI = ImageIO.read(fighterPicture);

		// Create elements that will hold pixel color information from the pixel
		// neighborhood
		int red[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		int green[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		int blue[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		Color c;

		/* Gather color information for all pixels in the neighborhood */
		int imgWidth = fighterBI.getWidth();
		int imgHeight = fighterBI.getHeight();
		int pixelsCounted = 0;
		int median = 0;

		/*for each pixel, determine its neighborhood and collect all other local pixel color data*/
		// info
		for (int y = 0; y < imgHeight - 1; y++) {
			for (int x = 0; x < imgWidth - 1; x++) {
				pixelsCounted = 0;
				for (int y2 = y - 1; y2 < y + 2; y2++) {
					for (int x2 = x - 1; x2 < x + 2; x2++) {
						if (x2 > imgWidth || x2 < 0)
							continue;

						if (y2 < 0 || y2 > imgHeight)
							continue;

						// for this pixel, grab its rgb values
						c = new Color(fighterBI.getRGB(x2, y2));
						red[pixelsCounted] = c.getRed();
						green[pixelsCounted] = c.getGreen();
						blue[pixelsCounted] = c.getBlue();

						pixelsCounted++;
					}
				}

				/* Use neighborhood data to determine the result for the currently inspected pixel*/
				Arrays.sort(red);
				Arrays.sort(green);
				Arrays.sort(blue);

				if (filterType == 1) { // median filter
					path = "Images/fighter_median_filtered.jpg";
					median = pixelsCounted / 2;
					if (pixelsCounted % 2 == 0) {
						red[median] = ((red[median] + red[median - 1]) / 2);
						green[median] = ((green[median] + green[median - 1]) / 2);
						blue[median] = ((blue[median] + blue[median - 1]) / 2);
					}

					// assign the median pixel color values from the neighborhood
					fighterBI.setRGB(x, y, new Color(red[median], green[median], blue[median]).getRGB());

				} else if (filterType == 2) { // image averaging
					path = "Images/fighter_average_filtered.jpg";
					int avgRed = 0, avgGreen = 0, avgBlue = 0;

					for (int i = 0; i < pixelsCounted; i++) {
						avgRed += red[i];
					}

					for (int i = 0; i < pixelsCounted; i++) {
						avgGreen += green[i];
					}

					for (int i = 0; i < pixelsCounted; i++) {
						avgBlue += blue[i];
					}

					avgRed /= pixelsCounted;
					avgGreen /= pixelsCounted;
					avgBlue /= pixelsCounted;

					// assign the average pixel color from the colors in the pixel neighborhood
					fighterBI.setRGB(x, y, new Color(avgRed, avgGreen, avgBlue).getRGB());
				}
			}
		}

		// write new filtered image
		File filteredImage = new File(path);
		ImageIO.write(fighterBI, "png", filteredImage);
	}
}
