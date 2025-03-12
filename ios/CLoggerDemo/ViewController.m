#import "ViewController.h"
#import "OCLogger.h"
#import "DemoT.h"
#import "NativeCLogger.h"
#import "OCLoggerIOSWrapper.h"

@interface ViewController ()

@property (nonatomic,assign) BOOL isEnablePrintable;
@property (nonatomic,assign) BOOL isEnableSavefile;
@property (nonatomic,assign) BOOL isEnableLogan;

@property (weak, nonatomic) IBOutlet UIButton *btn1;
@property (weak, nonatomic) IBOutlet UIButton *btn2;
@property (weak, nonatomic) IBOutlet UIButton *btn3;
@property (weak, nonatomic) IBOutlet UIButton *btn4;
@property (weak, nonatomic) IBOutlet UIButton *btn5;
@property (weak, nonatomic) IBOutlet UIButton *btn6;
@property (weak, nonatomic) IBOutlet UIButton *btn7;
@property (weak, nonatomic) IBOutlet UIButton *btn8;

@end

@implementation ViewController

- (void)viewDidLoad {
    NSLog(@"ViewController viewDidLoad");
    [super viewDidLoad];
    self.isEnablePrintable = TRUE;
    self.isEnableSavefile = TRUE;
    self.isEnableLogan = TRUE;
    [self.btn1 addTarget:self action:@selector(btn1Click) forControlEvents:UIControlEventTouchUpInside];
    [self.btn2 addTarget:self action:@selector(btn2Click) forControlEvents:UIControlEventTouchUpInside];
    [self.btn3 addTarget:self action:@selector(btn3Click) forControlEvents:UIControlEventTouchUpInside];
    [self.btn4 addTarget:self action:@selector(btn4Click) forControlEvents:UIControlEventTouchUpInside];
    [self.btn5 addTarget:self action:@selector(btn5Click) forControlEvents:UIControlEventTouchUpInside];
    [self.btn6 addTarget:self action:@selector(btn6Click) forControlEvents:UIControlEventTouchUpInside];
    [self.btn7 addTarget:self action:@selector(btn7Click) forControlEvents:UIControlEventTouchUpInside];
    [self.btn8 addTarget:self action:@selector(btn8Click) forControlEvents:UIControlEventTouchUpInside];
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
    DemoT *demoT = [[DemoT alloc] init];
    for(int i=0;i<200;i++)
    {
        [[CLogger shareInstance] debug:demoT message:[NSString stringWithFormat:@"打印日志8，index：%d",i]];
    }
}

// 多线程写20000次日志
- (void) btn3Click
{
    DemoT *demoT = [[DemoT alloc] init];
    dispatch_queue_t queue = dispatch_queue_create("btn3Click", DISPATCH_QUEUE_CONCURRENT);
    for (int i=0; i<500000; i++) {
        dispatch_async(queue, ^{
            [[CLogger shareInstance] debug:demoT message:[NSString stringWithFormat:@"打印日志9，thread_id: [%@], index: %d",[NSThread currentThread].name,i]];
        });
    }
}

// 写Logan日志
- (void) btn4Click
{
    DemoT *demoT = [[DemoT alloc] init];
    [[CLoggerIOSWrapper shareInstance] savefileLogV:demoT msg:@"打印日志 verbose debug"];
    [[CLoggerIOSWrapper shareInstance] savefileLogD:demoT msg:@"打印日志 debug debug"];
    [[CLoggerIOSWrapper shareInstance] savefileLogI:demoT msg:@"打印日志 info debug"];
    [[CLoggerIOSWrapper shareInstance] savefileLogW:demoT msg:@"打印日志 warn debug"];
    [[CLoggerIOSWrapper shareInstance] savefileLogE:demoT msg:@"打印日志 error debug"];
    
    [[CLoggerIOSWrapper shareInstance] loganLogV:demoT msg:@"打印日志 verbose debug"];
    [[CLoggerIOSWrapper shareInstance] loganLogD:demoT msg:@"打印日志 debug debug"];
    [[CLoggerIOSWrapper shareInstance] loganLogI:demoT msg:@"打印日志 info debug"];
    [[CLoggerIOSWrapper shareInstance] loganLogW:demoT msg:@"打印日志 warn debug"];
    [[CLoggerIOSWrapper shareInstance] loganLogE:demoT msg:@"打印日志 error debug"];
}

// 关闭Printable
- (void) btn5Click
{
    self.isEnablePrintable = !self.isEnablePrintable;
    if(_isEnablePrintable)
    {
        [self.btn5 setTitle:@"关闭Printable日志" forState:UIControlStateNormal];
    }else{
        [self.btn5 setTitle:@"开启Printable日志" forState:UIControlStateNormal];
    }
    [CLogger shareInstance].isPrintable = self.isEnablePrintable;
}

// 关闭SAVEFILE
- (void) btn6Click
{
    self.isEnableSavefile = !self.isEnableSavefile;
    if(_isEnableSavefile){
        [self.btn6 setTitle:@"关闭Savefile日志" forState:UIControlStateNormal];
    }else{
        [self.btn6 setTitle:@"开启Savefile日志" forState:UIControlStateNormal];
    }
    [CLogger shareInstance].isSaveFile = self.isEnableSavefile;
}

// 关闭Logan
- (void) btn7Click
{
    self.isEnableLogan = !self.isEnableLogan;
    if(_isEnableLogan){
        [self.btn7 setTitle:@"关闭Logan日志" forState:UIControlStateNormal];
    }else{
        [self.btn7 setTitle:@"开启Logan日志" forState:UIControlStateNormal];
    }
    [CLogger shareInstance].isLogan = _isEnableLogan;
}

- (void) btn8Click
{
    testPrint();
}

@end
