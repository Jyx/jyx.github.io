---
layout: post
title: Sibylla - Unlimited discount coupons
date: 2018-08-19
comments: true
category: Hacking
authors:Joakim Bech
modified: 2018-08-19
---
# tl;dr
- The Sibylla app uses plain `HTTP`.
- Not any verification of email used when logging into the app.
- The Sibylla server stores whether a coupon has been consumed or not for a
  certain email address.
- The app doesn't use the stored information at the server to decide whether a
  coupon has been used or not for a certain email.
- The "consumed" value seems to be stored locally in the app.
- Wiping the data/cache in Android's app settings will clear everything and
  will enable the coupons again. I.e., it is possible to use the same
  discount/offer as many times you wish.
- A rouge person can "use up" all coupons for any email (from a server point of view).

<br>

# The long version
Sibylla is a company who has been serving fast food for decades in Sweden. I'm
just back from [DEF CON 26](https://www.defcon.org/html/defcon-26/dc-26-index.html) where I picked up a
[WiFi Pineapple Nano](https://wifipineapple.com/nano). When playing with the
pineapple I enabled the [DWall](https://www.wifipineapple.com/modules) module,
which basically sniffs plain HTTP traffic (i.e., non-encrypted). As a side
effect of Google deciding to marking plain `HTTP` as insecure in Google Chrome,
more and more sites have switched to use `HTTPS` only, but there are still
plenty of un-encrypted traffic on the net. Out of curiosity I connected my
mobile to the WLAN shared by the pineapple and watched for traffic on DWall. I
tried a couple of different apps, some where dead silent and some showed some
`URLs`, cookies and images. The Sibylla app seemed to communicate using plain
`HTTP` and this is what can be seen when starting the app.


```bash
http://www.sibylla.se/ui/services/CampaignService.ashx?requestType=getAllCoupons
http://www.sibylla.se/ui/services/CampaignService.ashx?requestType=getAllCampaigns
http://www.sibylla.se/ui/services/CampaignService.ashx?requestType=getAllCouponsForUser&userId=email_foo.bar@moo.com
```

All calls here gets a [JSON](https://en.wikipedia.org/wiki/JSON) encoded payload
in return, looking something like this.

getAllCoupons query returns:
```json
[
  {
    "pageId": 1969,
    "created": "2018-06-28 09:16",
    "stoppublish": "2018-09-03 00:00",
    "name": "Super Meal 2 för 99kr",
    "description": "Super Meal 2 för 99kr",
    "imageUrl": "http://sibylla.se/PageFiles/6301/2_st_Super_Meal_99kr.png"
  },
  {
    "pageId": 1970,
    "created": "2018-06-28 09:16",
    "stoppublish": "2018-09-03 00:00",
    "name": "10kr rabatt mjukglass",
    "description": "10kr rabatt mjukglass",
    "imageUrl": "http://sibylla.se/PageFiles/6305/10kr_rabatt_mjukglass.png"
  },
// ... and so on
]
```

And the user specific query (getAllCouponsForUser) returns something like this:
```json
[
  {
    "pageId": 1969,
    "created": "2018-06-28 09:16",
    "stoppublish": "2018-09-03 00:00",
    "name": "Super Meal 2 för 99kr",
    "description": "Super Meal 2 för 99kr",
    "imageUrl": "http://sibylla.se/PageFiles/6301/2_st_Super_Meal_99kr.png",
    "consumed": false
  },
  {
    "pageId": 1970,
    "created": "2018-06-28 09:16",
    "stoppublish": "2018-09-03 00:00",
    "name": "10kr rabatt mjukglass",
    "description": "10kr rabatt mjukglass",
    "imageUrl": "http://sibylla.se/PageFiles/6305/10kr_rabatt_mjukglass.png",
    "consumed": false
  },
// ... and so on
]
```
Basically the only difference is the `consumed` attribute.

# Coupons
In the app, Sibylla from time to time offer deals on various meals. They way it
works is that you go the "deals" in the app, where you are presented a couple of
different coupons. When you are buying corresponding meal you let the clerk
press the "use coupon" button and then you don't have to pay the full price,
simple and easy!

# What happens under the hood?
When I played around with it and used up a coupon I could see the following
message was sent to [sibylla.se](http://sibylla.se): 
```bash
http://www.sibylla.se/ui/services/CampaignService.ashx?requestType=consumeCoupon&pageId=1975&userId=410daeeb1b350a86defb583e08ebbf15
```
I.e., something is sent back to their servers indicating that a coupon has been
used and indeed when checking in the app it says that coupon already has been
used and it stays like that even if you kill / restart the app. Two things
caught my attention here.

1. `pageId`: This is the id for the coupon. Replacing this any other valid
   `pageId` from the query posted further up will mark the coupon as used in the
   Sibylla server for a certain user.
2. `userId`: What is that? It looks like a hash of some sort. Is it a has of
   the `userId` for the app? Or the hash of the email? Or something else?

I decompiled the apk-file (using zip,
[dex2jar](https://github.com/pxb1988/dex2jar) and [jd-gui](http://jd.benow.ca))
and then looked up the keyword `consumeCoupon`, which revealed:

```java
    public UsedDealResponse loadDataFromNetwork() throws Exception {
        Builder campaignUriBuilder = Uri.parse(Constants.campaignService).buildUpon();
        campaignUriBuilder.appendQueryParameter("requestType", "consumeCoupon");
        campaignUriBuilder.appendQueryParameter("pageId", this.pageId);
        campaignUriBuilder.appendQueryParameter("userId", this.userId);
        String url = campaignUriBuilder.build().toString();
        Log.m17i("URL " + url);
        return (UsedDealResponse) getRestTemplate().getForObject(url, UsedDealResponse.class, new Object[0]);
    }
```

and where `userId` seems to come from
```java
    public UseDealsRequest(String userId, String pageId) {
        super(UsedDealResponse.class);
        this.userId = md5(userId);
        Log.m17i("MD5 " + this.userId);
        this.pageId = pageId;
    }
```

There we have it, the `userId` is a `MD5` sum of something. After some fiddling
I understood that is comes from the string if you used email when logging into
the app. I guess it would be slightly different when using Facebook or Google
login.

```bash
    md5("email_foo.bar@moo.com") = 410daeeb1b350a86defb583e08ebbf15
```

So, let's recap:

- The app queries the server on start.
- The app sends a `consumeCoupon` message to the server when using a coupon,
  but instead of plain email it is using the `MD5` of the string "`email_...`" as
  the `userId`.

<br>

# Re-use a coupon?
I wondered how they protected against using a coupon more than once. I searched
the decompiled code for other `requestType`. But I couldn't find anything
indicating that it was possible to revert a used coupon (server side). But at
the same time, I've noticed that the app uses the email string when starting
the app, but using an `MD5` sum of the app when using a coupon. Something
doesn't seem right here. Calling:

```bash
http://www.sibylla.se/ui/services/CampaignService.ashx?requestType=getAllCouponsForUser&userId=email_foo.bar@moo.com
```
and
```bash
http://www.sibylla.se/ui/services/CampaignService.ashx?requestType=getAllCouponsForUser&userId=410daeeb1b350a86defb583e08ebbf15
```
gives different result. The former tells you that no coupon has been used, but
the latter will indeed tell you that the ones you've used up indeed are marked
as `consumed: true`. So, how can the app know that a coupon has been used?
Could it be stored locally? Said and done, I cleared the Sibylla apps data and
cache. Restarted the app, logged in with the same email and voilá, the app
tells me that the coupon hasn't been used. This must mean that the app is
indeed storing data locally.

# Reflections
I guess a company like Sibylla probably doesn't care too much about this. Since
in the end they're probably happy as long as they sell their fast food and they
probably makes a nice profit even when their customers are using a discount
code or something similar. But, since they walked the extra mile of letting
someone create an app like this, I guess there is some interest of having e
genuine app behaving as expected. There are mainly three things that seems
wrong here:

- The app stores data at a server, but the app doesn't seem to make use of this
  information. I cannot say whether that is a bug due to using a plain string
  when starting the app and using the `MD5` of the string when using a coupon or
  if all this is intentional and the server part is just there for statistics for
  Sibylla marketing.
- It is possible to re-use coupons by just clear the data/cache for the app.
- Since there is no authentication, it is possible to exploit and put false
  information at their server, by just use any combination with `userId/pageId`.

<br>

# What could and should be done?
- The app should use `HTTPS` instead of plain `HTTP`. If that would have been
  the case, then this would never caught my attention.
- The email used then logging into the app should be authenticated.
- The server should only accept requests from authenticated users.
- The app should use the data from the server to decide whether a user already
  has used a coupon or not.

This doesn't seem like a super serious issue, but I've given Sibylla knowledge
about it 2018-08-19 and as common practice I'll give them a 90 days to fix the
issues I've found. I.e., somewhere after the 17th November 2018 I'll publish
this article on my site.
