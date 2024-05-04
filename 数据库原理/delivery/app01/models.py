from django.db import models

# Create your models here.
# 对数据库操作


# create app01_userinfo
class UserInfo(models.Model):
    name = models.CharField(max_length=50)
    password = models.CharField(max_length=64)
    phone = models.CharField(max_length=50)
    address = models.CharField(max_length=30)


class MenuInfo(models.Model):
    name = models.CharField(max_length=50)
    price = models.CharField(max_length=10)
    marketer = models.CharField(max_length=50)


class MarketerInfo(models.Model):
    material = models.CharField(max_length=50)
    staff = models.CharField(max_length=50)