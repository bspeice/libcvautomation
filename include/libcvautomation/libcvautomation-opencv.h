/*
 * =====================================================================================
 *
 *       Filename:  libcvautomation-opencv.h
 *
 *    Description:  Function definitions for opencv functionality
 *
 *        Created:  06/21/2012 08:34:21 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Bradlee Speice, bspeice@uncc.edu
 *   Organization:  MOSAIC at University of North Carolina at Charlotte
 *
 * =====================================================================================
 */
#ifndef LIBCVAUTOMATION_OPENCV_H
#define LIBCVAUTOMATION_OPENCV_H

#include <libcvautomation/libcvautomation.h>

/* It should be noted that the following are the macros for template matching:
 * 	CV_TM_SQDIFF (default)
 *  CV_TM_SQDIFF_NORMED
 *  CV_TM_CCORR
 *  CV_TM_CCORR_NORMED
 *  CV_TM_CCOEFF
 *  CV_TM_CCOEFF_NORMED
 */

/* Match a root image and sub image */
CvPoint matchSubImage ( IplImage *rootImage, IplImage *subImage, int searchMethod, double tolerance );

/* Match a root image and sub image, return the center */
CvPoint matchSubImage_center ( IplImage *rootImage, IplImage *subImage, int searchMethod, double tolerance );

/* Match a root image and sub image from filename */
CvPoint matchSubImage_location ( const char *rootImage_location, const char *subImage_location, int searchMethod, double tolerance );

/* Match a root image and sub image from filename, return the center */
CvPoint matchSubImage_location_center ( const char *rootImage_location, const char *subImage_location, int searchMethod, double tolerance );

/* Match a root image and sub images from an array of images */
void matchSubImage_a ( IplImage *rootImage, cvautomationList *subImageArray, int listSize );

/* Match a root image and sub images from an array of images, return the center */
void matchSubImage_a_center ( IplImage *rootImage, cvautomationList *subImageArray, int listSize );

/* Match a root image and sub images from an array of images */
void matchSubImage_a_location ( const char *rootImageFileName, cvautomationList *subImageArray, int listSize );

/* Match a root image and sub images from an array of images, return the center */
void matchSubImage_a_location_center ( const char *rootImageFileName, cvautomationList *subImageArray, int listSize );

#endif /* LIBCVAUTOMATION_OPENCV_H */

/* Doxygen information */
/** \file libcvautomation-opencv.h
 * \brief The source code to access libcv from inside libcvautomation.
 * \details This source file builds in the necessary functionality to use libcv functions inside libcvautomation.
 * \author Bradlee Speice
 * \date 7/18/2012
 */

/** \page libcvautomation_search_methods Libcv Search Methods
This page describes the methods libcv uses to search for a sub image in a root image.
\section tolerance Tolerance Values
Tolerance values are used to control how strict each of the following search methods are. Acceptable values are from \c INT_MIN to \c INT_MAX.

Additionally, each of the reference programs - \c cva-input and \c cva-match - have a "sane tolerance" built in. This is accessed by the "-o" switch, and allows you to specify a tolerance on scale of 1-100, where 1 is incredibly strict, and 100 is incredibly loose.
\note The formula for calculating the sane tolerance is: \f$ T(x) = (10^{\frac{\log{INT\_MAX}}{\lambda}})^x \f$ where \f$ \lambda \f$ is the highest tolerance value (in our case, 100). Finally, we have to round down a little bit to ensure that we don't accidentally generate a value higher than \c INT_MAX. The formula used does mean that we will never be able to generate values lower than 0.
\warning The "sane-tolerance" option doesn't know which search method you are using - Thus while 1 is an incredibly strict search for \ref SQDIFF and \ref SQDIFF_NORMED, it is fairly loose search for \ref CCORR, \ref CCORR_NORMED, \ref CCOEFF, and \ref CCOEFF_NORMED

\section SQDIFF Squared Difference
\code #define CV_TM_SQDIFF	0 \endcode
Squared Difference is the default search method used by \c libcvautomation, as well as \c cva-match and \c cva-input.
\par For this method, setting a low tolerance value results in a more strict match.

Formula:
\f$R(x,y) = \sum_{x',y'} (T(x',y') - I(x + x', y+y'))^2 \f$

\section SQDIFF_NORMED Squared Difference (Normalized)
\code #define CV_TM_SQDIFF_NORMED	1 \endcode
This is a normalized version of the \ref SQDIFF search method.
\par For this method, setting a low tolerance value results in a more strict match.

Formula:
\f$ R(x,y) = \frac{\sum_{x',y'}(T(x',y') - I(x + x', y + y'))^2}{ \sqrt{\sum_{x',y'}T(x',y')^2 \cdot \sum_{x',y'}I(x + x', y + y')^2}} \f$

\section CCORR Cross Correlation
\code #define CV_TM_CCORR	2 \endcode
This is the Cross Correlation search method.
\par For this method, setting a high tolerance value results in a more strict match.

Formula:
\f$ R(x,y)= \sum _{x',y'} (T(x',y') \cdot I(x+x',y+y')) \f$

\section CCORR_NORMED Cross Correlation (Normalized)
\code #define CV_TM_CCORR_NORMED	3 \endcode
This is the normalized version of the \ref CCORR search method.
\par For this method, setting a high tolerance value results in a more strict match.

Formula:
\f$ R(x,y)= \frac{\sum_{x',y'} (T(x',y') \cdot I'(x+x',y+y'))}{\sqrt{\sum_{x',y'}T(x',y')^2 \cdot \sum_{x',y'} I(x+x',y+y')^2}} \f$

\section CCOEFF Correlation Coefficient
\code #define CV_TM_CCOEFF	4 \endcode
This is the Correlation Coefficient search method.
\par For this method, setting a high tolerance value results in a more strict match.

Formula:
\f$ R(x,y)= \sum _{x',y'} (T'(x',y') \cdot I(x+x',y+y')) \f$
where:
\f$ \begin{array}{l} T'(x',y')=T(x',y') - 1/(w \cdot h) \cdot \sum _{x'',y''} T(x'',y'') \\ I'(x+x',y+y')=I(x+x',y+y') - 1/(w \cdot h) \cdot \sum _{x'',y''} I(x+x'',y+y'') \end{array} \f$

\section CCOEFF_NORMED Correlation Coefficient (Normalized)
\code #define CV_TM_CCOEFF_NORMED	5 \endcode
This is the normalized version of the \ref CCOEFF search method.
\par For this method, setting a high tolerance value results in a more strict match.

Formula:
\f$ R(x,y)= \frac{ \sum_{x',y'} (T'(x',y') \cdot I'(x+x',y+y')) }{ \sqrt{\sum_{x',y'}T'(x',y')^2 \cdot \sum_{x',y'} I'(x+x',y+y')^2} } \f$
 */


/** \fn CvPoint matchSubImage ( IplImage *rootImage, IplImage *subImage, int searchMethod, double tolerance );
 * \brief Return the location of a sub image in its root image
 * \param rootImage The root image (in IplImage format) to search in
 * \param subImage The sub image (in IplImage format) to search for in \c rootImage
 * \param searchMethod The search method to use when searching for \c subImage in \c rootImage.
 * \param tolerance The tolerance to use when searching for \c subImage in \c rootImage.
 * \see \ref libcvautomation_search_methods
 * \return The location of the sub image in root image
 */

/** \fn CvPoint matchSubImage_center ( IplImage *rootImage, IplImage *subImage, int searchMethod, double tolerance );
 * \brief Return the center of a sub image in its root image, rather than the top-left corner
 * \param rootImage The root image (in IplImage format) to search in
 * \param subImage The sub image (in IplImage format) to search for in \c rootImage
 * \param searchMethod The search method to use when searching for \c subImage in \c rootImage.
 * \param tolerance The tolerance to use when searching for \c subImage in \c rootImage.
 * \see \ref libcvautomation_search_methods
 * \return The center location of the sub image in root image
 */

/** \fn CvPoint matchSubImage_location ( const char *rootImage_location, const char *subImage_location, int searchMethod, double tolerance );
 * \brief Return the location of a sub image in its root image
 * \details The difference that this function has over matchSubImage() is that \e rootImage_location and \e subImage_location are from files, rather than an IplImage format image.
 * \param rootImage_location The location of the root image
 * \param subImage_location The location of the sub image to search for in \c rootImage
 * \param searchMethod The search method to use when searching for \c subImage in \c rootImage.
 * \param tolerance The tolerance to use when searching for \c subImage in \c rootImage.
 * \see \ref libcvautomation_search_methods
 * \return The location of the sub image in root image
 */

/** \fn CvPoint matchSubImage_location_center ( const char *rootImage_location, const char *subImage_location, int searchMethod, double tolerance );
 * \brief Return the center of a sub image in its root image, rather than the top-left corner
 * \details The difference that this function has over matchSubImage_center() is that \e rootImage_location and \e subImage_location are from files, rather than an IplImage format image.
 * \param rootImage_location The location of the root image
 * \param subImage_location The location of the sub image to search for in \c rootImage
 * \param searchMethod The search method to use when searching for \c subImage in \c rootImage.
 * \param tolerance The tolerance to use when searching for \c subImage in \c rootImage.
 * \see \ref libcvautomation_search_methods
 * \return The center location of the sub image in root image
 */

/** \fn void matchSubImage_a ( IplImage *rootImage, cvautomationList *subImageArray, int listSize );
 * \brief Parse an array of sub images and send them to matchSubImage()
 * \param rootImage The root image (in IplImage format) to search in
 * \param subImageArray The sub image array to search for in \c rootImage - Note that the contents of \c subImageArray are modified during execution of this routine
 * \param listSize The number of sub images to search for in subImageArray
 * \see cvautomationList
 * \return This function returns void, and modifies the contents of subImageArray
 */

/** \fn void matchSubImage_a_center ( IplImage *rootImage, cvautomationList *subImageArray, int listSize );
 * \brief Parse an array of sub images and send them to matchSubImage_center()
 * \details Uses the cvautomationList.cvaImage parameter to find a \c subImage in \c rootImage
 * \param rootImage The root image (in IplImage format) to search in
 * \param subImageArray The sub image array to search for in \c rootImage - Note that the contents of \c subImageArray are modified during execution of this routine
 * \param listSize The number of sub images to search for in subImageArray
 * \see cvautomationList
 * \return This function returns void, and modifies the contents of subImageArray
 */

/** \fn void matchSubImage_a_location ( const char *rootImage_location, cvautomationList *subImageArray, int listSize );
 * \brief Parse an array of sub images and send them to matchSubImage()
 * \details The difference between this and matchSubImage_a() is that this uses a root image from filename, rather than from an IplImage format.
 * \param rootImage_location The location of the root image
 * \param subImageArray The sub image array to search for in \c rootImage_location - Note that the contents of \c subImageArray are modified during execution of this routine
 * \param listSize The number of sub images to search for in subImageArray
 * \see cvautomationList
 * \return This function returns void, and modifies the contents of subImageArray
 */

/** \fn void matchSubImage_a_location_center ( const char *rootImage_location, cvautomationList *subImageArray, int listSize );
 * \brief Parse an array of sub images and send them to matchSubImage_center()
 * \details The difference that this function has over matchSubImage_a_center() is that \c rootImage_location is from a file
 * \param rootImage_location The location of the root image
 * \param subImageArray The sub image array to search for in \c rootImage_location - Note that the contents of \c subImageArray are modified during execution of this routine
 * \param listSize The number of sub images to search for in subImageArray
 * \see cvautomationList
 * \return This function returns void, and modifies the contents of subImageArray
 */
