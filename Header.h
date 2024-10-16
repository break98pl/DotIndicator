@interface SBIcon : NSObject
-(id)applicationBundleID;
-(void)_notifyAccessoriesDidUpdate;
-(void)setIsEditing:(BOOL)arg1 ;
-(void)setOverrideBadgeNumberOrString:(id)arg1 ;
-(id)badgeValue;
-(long long)accessoryTypeForLocation:(id)arg1 ;
@end

@interface SBFolder : NSObject
-(NSArray *)lists;
-(id)listsContainingLeafIconWithIdentifier:(id)arg1 ;
-(id)folderIcons;
-(void)setBadge:(NSString *)arg1 ;
-(SBIcon *)icon;
-(NSString *)badge;
-(BOOL)isOpen;
-(void)removeBadgeFolder;
+(id)sharedInstance;
@end

@interface SBFolderIcon: SBIcon
-(SBFolder *)folder;
@end

@interface SBIconViewMap : NSObject 
-(id)mappedIconViewForIcon:(id)arg1;
- (id)iconViewForIcon:(id)arg1;
- (id)_iconViewForIcon:(id)arg1;
@end

@interface SBFloatyFolderController : NSObject 
-(SBFolder *)folder;
@end

@interface SBApplicationProcessState : NSObject
@property (getter=isRunning, nonatomic, readonly) BOOL running;
@property (getter=isForeground, nonatomic, readonly) BOOL foreground;
-(int)taskState;
-(int)visibility;
@end

@interface SBIconListModel : NSObject
-(id)icons;
@end

@interface SBApplication : NSObject
@property (nonatomic, readonly) SBApplicationProcessState *processState;
-(NSString *)bundleIdentifier;
-(NSString *)bundleId;
-(void)setBadgeValue:(NSNumber*)val;
-(void)setBadgeNumberOrString:(id)arg1 ;
-(id)badgeNumberOrString;
-(id)applicationWithDisplayIdentifier:(id)arg1 ;
@end

@interface SBApplicationIcon : SBIcon
-(SBApplication *)application;
@property (nonatomic,readonly) NSString * bundleIdentifier;  
@end

@interface SBIconView : UIView
@property (nonatomic,retain) SBIcon * icon;
@property (nonatomic, retain) UIView *runningIndicator;
@property (nonatomic,copy) NSString * location;
- (id)initWithContentType:(unsigned long long)arg1;
-(id)initWithDefaultSize;
-(void)setBounds:(CGRect)arg1 ;
@end

@interface SBApplicationController : NSObject
+(id)sharedInstance;
-(id)applicationWithBundleIdentifier:(id)arg1;
@end

@interface SBIconBadgeView : NSObject
+(id)sharedInstance;
-(id)applicationWithBundleIdentifier:(id)arg1;
@end

@interface SBIconListView : UIView
-(void)updateRunningIndicators:(NSNotification *)notification;
-(SBIconViewMap *)viewMap;
-(SBIconListModel *)model;
@end

@interface SBHIconModel : NSObject
-(void)reloadIcons;
@property (assign,getter=isRestoring,nonatomic) BOOL restoring;
@end

@interface SBIconModel : SBHIconModel
-(id)applicationWithBundleIdentifier:(id)arg1 ;
-(SBApplicationIcon *)applicationIconForBundleIdentifier:(id)arg1 ;
-(id)expectedIconForDisplayIdentifier:(id)arg1 ;
-(id)applicationIconForDisplayIdentifier:(id)arg1 ;
-(id)leafIconForIdentifier:(id)arg1 ;
+(id)homescreenMap;
-(SBIcon *)rootFolderIcon;
@end

@interface SBRootIconListView : SBIconListView
@end

@interface SBIconController : UIViewController
+(id)sharedInstance;
-(SBIconModel *)model;
-(SBIconViewMap *)homescreenIconViewMap;
-(SBRootIconListView *)currentRootIconList;
@end

@interface SBIconImageView : UIView
@property (nonatomic, strong) UISwipeGestureRecognizer *swipeGestureRecognizer;
- (UIImage *)contentsImage;
- (void)appDataPreferencesChanged;
-(SBIcon *)icon;
@property (assign,nonatomic) SBIconView * iconView;
@property (nonatomic, retain) UIView *badgeView; // new
@property (nonatomic, retain) UILabel *timeLeftLabel; // new
- (void)setupBadgeView ; // new
- (void)updateBadgeView:(id)arg1 ; // new
@end

@interface SBMainSwitcherViewController: UIViewController
+ (id)sharedInstance;
- (id)recentAppLayouts;
-(void)_deleteAppLayoutsMatchingBundleIdentifier:(id)arg1 ;
@end

@interface SBAppLayout : NSObject
-(NSDictionary *)rolesToLayoutItemsMap;
@end
