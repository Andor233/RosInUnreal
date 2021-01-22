// Fill out your copyright notice in the Description page of Project Settings.


#include "RosActor.h"

#include "ros/ros.h"
#include "std_msgs/String.h"

class ARosActor::Impl {
    ros::NodeHandle n{};
    ros::Subscriber subscriber;
public:
    int cnt = 0;
    bool flag = true;
   ros::Publisher chatter_pub = n.advertise<std_msgs::String>("/chatter", 1000);

    void subscribe() {
        UE_LOG(LogTemp, Warning, TEXT("before function"));
        boost::function<void(const std_msgs::String &)> callback =
                [&](const std_msgs::String &msg) {
                    FString data(msg.data.c_str());
                    UE_LOG(LogTemp, Warning, TEXT("%s"), *data);
        };
        UE_LOG(LogTemp, Warning, TEXT("before Subscribe"));
        subscriber = n.subscribe<std_msgs::String>("/chatter", 10, callback);
        UE_LOG(LogTemp, Warning, TEXT("after Subscribe"));
    };

    static void init() {
        std::string s("RosUnreal");
        std::map<std::string, std::string> m_string{
                {"__master",   "http://127.0.0.1:11311/"},
                {"__ip",       "127.0.0.1"},
                {"__hostname", "127.0.0.1"}
        };
        ros::init(m_string, s);
        UE_LOG(LogTemp, Warning, TEXT("Init"));
    }

    static void shutdown() {
        ros::shutdown();
        UE_LOG(LogTemp, Warning, TEXT("Shutdown"));
    }

    void SpinOnce() {
        ros::spinOnce();
//        UE_LOG(LogTemp, Warning, TEXT("Spin"));
    }
};

// Sets default values
ARosActor::ARosActor() {
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARosActor::BeginPlay() {
    Super::BeginPlay();
    Impl::init();
    pimpl = new Impl();
}

// Called every frame
void ARosActor::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    if (pimpl->flag) {
        pimpl->subscribe();
        pimpl->flag = false;
    } else {
       std_msgs::String msg;
       msg.data = "Hello";
       pimpl->chatter_pub.publish(msg);
        pimpl->SpinOnce();
//        UE_LOG(LogTemp, Warning, TEXT("Count: %d"), pimpl->cnt);
    }
}

