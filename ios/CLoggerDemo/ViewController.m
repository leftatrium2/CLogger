#import "ViewController.h"
#import "OCLogger.h"
#import "DemoT.h"

@interface ViewController ()

@property (weak, nonatomic) IBOutlet UIButton *btn1;
@property (weak, nonatomic) IBOutlet UIButton *btn2;
@property (weak, nonatomic) IBOutlet UIButton *btn3;
@property (weak, nonatomic) IBOutlet UIButton *btn4;
@property (weak, nonatomic) IBOutlet UIButton *btn5;
@property (weak, nonatomic) IBOutlet UIButton *btn6;
@property (weak, nonatomic) IBOutlet UIButton *btn7;

@end

@implementation ViewController

- (void)viewDidLoad {
    NSLog(@"ViewController viewDidLoad");
    [super viewDidLoad];
    [self.btn1 addTarget:self action:@selector(btn1Click) forControlEvents:UIControlEventTouchUpInside];
    [self.btn2 addTarget:self action:@selector(btn2Click) forControlEvents:UIControlEventTouchUpInside];
    [self.btn3 addTarget:self action:@selector(btn3Click) forControlEvents:UIControlEventTouchUpInside];
    [self.btn4 addTarget:self action:@selector(btn4Click) forControlEvents:UIControlEventTouchUpInside];
    [self.btn5 addTarget:self action:@selector(btn5Click) forControlEvents:UIControlEventTouchUpInside];
    [self.btn6 addTarget:self action:@selector(btn6Click) forControlEvents:UIControlEventTouchUpInside];
    [self.btn7 addTarget:self action:@selector(btn7Click) forControlEvents:UIControlEventTouchUpInside];
}

// 点击打印日志
- (void) btn1Click
{
    DemoT *demoT = [[DemoT alloc] init];
    [[CLogger shareInstance] debug:@"btn1Click 打印日志1"];
    [[CLogger shareInstance] debug:demoT message:@"btn1Click 打印日志2"];
    [[CLogger shareInstance] verbose:@"btn1Click 打印verbose日志"];
    [[CLogger shareInstance] info:@"btn1Click 打印info日志"];
    [[CLogger shareInstance] warn:@"btn1Click 打印warning日志"];
    [[CLogger shareInstance] error:@"btn1Click 打印error日志"];
    [[CLogger shareInstance] crash:@"btn1Click 打印Crash日志"];
    [[CLogger shareInstance] wtf:@"btn1Click 打印wtf日志"];
}

// 写200次日志
- (void) btn2Click
{
    NSLog(@"btn2Click");
}

// 多线程写20000次日志
- (void) btn3Click
{
    NSLog(@"btn3Click");
}

// 写Logan日志
- (void) btn4Click
{
    NSLog(@"btn4Click");
}

// 关闭Printable
- (void) btn5Click
{
    NSLog(@"btn5Click");
}

// 关闭SAVEFILE
- (void) btn6Click
{
    NSLog(@"btn6Click");
}

// 关闭Logan
- (void) btn7Click
{
    NSLog(@"btn7Click");
}

@end
