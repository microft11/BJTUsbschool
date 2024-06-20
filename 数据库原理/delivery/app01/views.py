from django.shortcuts import render, HttpResponse, redirect, get_object_or_404
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
        # return HttpResponse("hello")
        return redirect("http://127.0.0.1:8000/menu/info")

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
    data_list = MenuInfo.objects.all()
    return render(request, "auth_way.html", {"data_list":data_list})

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
    

def user_edit(request, user_id):
    user = get_object_or_404(UserInfo, id=user_id)
    if request.method == "GET":
        return render(request, "user_edit.html", {"user": user})
    else:
        user.name = request.POST.get("user")
        user.password = request.POST.get("password")
        user.phone = request.POST.get("phone")
        user.address = request.POST.get("address")
        user.save()
        return redirect("http://127.0.0.1:8000/user/info")

def user_delete(request, user_id):
    user = get_object_or_404(UserInfo, id=user_id)
    user.delete()
    return redirect("http://127.0.0.1:8000/user/info")

def menu_edit(request, menu_id=None):
    print("hello")
    print(menu_id)
    if menu_id is None:
        # 处理未提供menu_id的情况，例如重定向或返回错误
        return redirect("http://127.0.0.1:8000/menu/info")
    
    menu = get_object_or_404(MenuInfo, id=menu_id)
    if request.method == "GET":
        return render(request, "menu_edit.html", {"menu": menu})
    else:
        menu.name = request.POST.get("name")
        menu.price = request.POST.get("price")
        # 继续处理其他字段
        menu.save()
        return redirect("http://127.0.0.1:8000/menu/info")


def menu_delete(request, menu_id):
    menu = get_object_or_404(MenuInfo, id=menu_id)
    menu.delete()
    return redirect("http://127.0.0.1:8000/menu/info")