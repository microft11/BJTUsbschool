from django.shortcuts import render, HttpResponse, redirect
from app01.models import UserInfo, MenuInfo, MarketerInfo

# Create your views here.
# url 会写在这

def index(request):
    return HttpResponse("hello world!!")

def login(request):
    if request.method == "GET":
        return render(request, "login.html")
    else:
        print(request.POST)
        username = request.POST.get("user")
        password = request.POST.get("password")

        print(username, password)
        return HttpResponse("hello")

def user_info_list(request):
    data_list = UserInfo.objects.all()

    return render(request, "user_info_list.html", {"data_list":data_list})

def user_add(request):
    if request.method == "GET":
        return render(request, "user_add.html")

    # 现在是收到用户提交的信息
    user = request.POST.get("user")
    password = request.POST.get("password")
    phone = request.POST.get("phone")
    address = request.POST.get("address")

    # 添加数据库
    if user and password:
        UserInfo.objects.create(name=user, password=password, phone=phone, address=address)

    print("add user")
    return redirect("http://127.0.0.1:8000/user/info")

def menu_info(request):
    data_list = MenuInfo.objects.all()

    return render(request, "menu_info.html", {"data_list":data_list})


def menu_find(request):
    if request.method == "GET":
        return HttpResponse("you shouldn't go there this time")

    # 现在是收到用户提交的信息
    name = request.POST.get("name")
    data_list = MenuInfo.objects.all()

    for item in data_list:
        print(item.name)
        if item.name == name:
            return render(request, "menu_find.html", {"name":name, "price":item.price})

    return HttpResponse("cant find this name in the menu")

def auth_way(request):
    return render(request, "auth_way.html")

def auth_add(request):
    if request.method == "GET":
        return HttpResponse("you shouldn't go there this time")

    name = request.POST.get("name")
    price = request.POST.get("price")
    marketer = request.POST.get("marketer")

    if name and price and marketer:
        MenuInfo.objects.create(name=name, price=price, marketer=marketer)

    print("add menu")
    return redirect("http://127.0.0.1:8000/menu/info")