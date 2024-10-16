#import <UIKit/UIKit.h>
#import "Header.h"

%hook SBApplication
-(void)_noteProcess:(id)arg1 didChangeToState:(id)arg2{
  %orig;
  if(![self.bundleIdentifier isEqual:@"com.apple.Spotlight"]){
    dispatch_async(dispatch_get_main_queue(), ^{
      if(self.processState){
        SBIcon *icon = [((SBIconController *)[objc_getClass("SBIconController") sharedInstance]).model applicationIconForBundleIdentifier:self.bundleIdentifier];
        if(self.processState.taskState == 2 && self.processState.visibility == 2){
        	[icon _notifyAccessoriesDidUpdate];
        }
        if(self.processState.taskState == 2 && self.processState.visibility == 1){
        	[icon _notifyAccessoriesDidUpdate];
        }
      }
    });
  }
}

-(void)_didExitWithContext:(id)arg{
  %orig;
  dispatch_async(dispatch_get_main_queue(), ^{
    SBIcon *icon = [((SBIconController *)[objc_getClass("SBIconController") sharedInstance]).model applicationIconForBundleIdentifier:self.bundleIdentifier];
    [icon _notifyAccessoriesDidUpdate];
  });
}
%end

%hook SBIconView

-(long long)currentLabelAccessoryType{
	SBApplicationIcon *applicationIcon = [((SBIconController *)[objc_getClass("SBIconController") sharedInstance]).model applicationIconForBundleIdentifier: self.icon.applicationBundleID];
	SBApplication *application = applicationIcon.application;
	if(application.processState){
		if(application.processState.visibility == 2){
			return 1;
		}
		else if(application.processState.visibility == 1){
			return 2;
		}
	}
	return 0;
}

-(CGRect)_frameForLabelAccessoryViewWithLabelFrame:(CGRect)arg1 labelImage:(id)arg2 labelImageParameters:(id)arg3 imageFrame:(CGRect)arg4{
	CGRect orig = %orig();
  if(![self.location containsString:@"Dock"]){
    orig.origin.x = 28;
    orig.origin.y = orig.origin.y + 14;
  }
	return orig;
}

%end

%hook SBIconImageView

%property (nonatomic, retain) UISwipeGestureRecognizer *swipeGestureRecognizer;

- (SBIconImageView *)initWithFrame:(CGRect)arg1 {
    SBIconImageView *r = %orig;
    if (![r isKindOfClass:NSClassFromString(@"SBFolderIconImageView")]) {
        // Create Gesture Recognizer
        self.swipeGestureRecognizer = [[UISwipeGestureRecognizer alloc] initWithTarget:r action:@selector(didSwipeUp:)];
        self.swipeGestureRecognizer.direction = (UISwipeGestureRecognizerDirectionUp);
        r.userInteractionEnabled = YES;
        
        // Add gesture if enabled
        [self addGestureRecognizer:self.swipeGestureRecognizer];
    }
    return r;
}

%new
- (void)didSwipeUp:(UIGestureRecognizer *)gesture {
    if (gesture.state == UIGestureRecognizerStateEnded) {
      dispatch_async(dispatch_get_main_queue(), ^{
        SBIcon *icon = self.icon;
        SBMainSwitcherViewController *mainSwitcher = [%c(SBMainSwitcherViewController) sharedInstance];
        [mainSwitcher _deleteAppLayoutsMatchingBundleIdentifier:icon.applicationBundleID];
      });
    }
}

%end
