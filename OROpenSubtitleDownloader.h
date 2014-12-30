//
//  ORSubtitleDownloader.h
//  Puttio
//
//  Created by orta therox on 08/12/2012.
//  Copyright (c) 2012 ortatherox.com. All rights reserved.
//

#import <XMLRPC/XMLRPC.h>

@class OROpenSubtitleDownloader, OpenSubtitleSearchResult;

typedef enum {
    OROpenSubtitleStateLoggingIn,
    OROpenSubtitleStateLoggedIn,
    OROpenSubtitleStateSearching,
    OROpenSubtitleStateDownloading,
    OROpenSubtitleStateDownloaded
} OROpenSubtitleState;


@protocol OROpenSubtitleDownloaderDelegate <NSObject>
@optional
- (void)openSubtitlerDidLogIn:(OROpenSubtitleDownloader *)downloader;

@end

/// OROpenSubtitleDownloader makes it easier to handle downloading and searching
/// for subtitles via the opensubtitles.org API

@interface OROpenSubtitleDownloader : NSObject <XMLRPCConnectionDelegate>

/// By using init the object will create it's own user agent based on bundle info
- (OROpenSubtitleDownloader *)init;

/// Use a custom user agent
- (OROpenSubtitleDownloader *)initWithUserAgent:(NSString *)userAgent;

/// The object that recieves notifications for new subtitles
@property (nonatomic, weak) NSObject <OROpenSubtitleDownloaderDelegate> *delegate;

/// Internal state of subtitle downloader
@property (nonatomic, readonly) OROpenSubtitleState state;

/// Language string, defaults to "eng", 
/// See: http://www.opensubtitles.org/addons/export_languages.php for full list
@property (nonatomic, strong) NSString *languageString;

/// Search and get a return block with an array of OpenSubtitleSearchResult
- (void)searchForSubtitlesWithHash:(NSString *)hash andFilesize:(NSNumber *)filesize :(void(^) (NSArray *subtitles))searchResult;

/// Downloads a subtitle result to a file after being unzipped
- (void)downloadSubtitlesForResult:(OpenSubtitleSearchResult *)result toPath:(NSString *)path :(void(^)())onResultsFound;
@end


@interface OpenSubtitleSearchResult : NSObject

+ (OpenSubtitleSearchResult *)resultFromDictionary:(NSDictionary *)dictionary;

@property (copy) NSString *subtitleID;
@property (copy) NSString *imdbID;
@property (copy) NSString *subtitleLanguage;
@property (copy) NSString *iso639Language;
@property (copy) NSString *subtitleDownloadAddress;

@end
