using System;
using Android.App;
using Android.OS;
using Android.Runtime;
using Android.Views;
using AndroidX.AppCompat.Widget;
using AndroidX.AppCompat.App;
using Google.Android.Material.FloatingActionButton;
using Google.Android.Material.Snackbar;
using Plugin.BLE;
using System.Collections.Generic;
using System.Threading;
using AndroidX.Core.Content;
using Android;
using Android.Content.PM;

namespace AndroidApp
{
    [Activity(Label = "@string/app_name", Theme = "@style/AppTheme.NoActionBar", MainLauncher = true)]
    public class MainActivity : AppCompatActivity
    {
        protected override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);
            Xamarin.Essentials.Platform.Init(this, savedInstanceState);
            SetContentView(Resource.Layout.activity_main);

            Toolbar toolbar = FindViewById<Toolbar>(Resource.Id.toolbar);
            SetSupportActionBar(toolbar);

            //搜索蓝牙设备
            var fabSearch = FindViewById<Google.Android.Material.Button.MaterialButton>(Resource.Id.btn_Search);
            fabSearch.Click += btnSearchOnClick;

            //连接
            var fabConnect = FindViewById<Google.Android.Material.Button.MaterialButton>(Resource.Id.btn_Connect);
            fabConnect.Click += btnConnectOnClick;

            //开启权限
            List<string> permissionList = new List<string>(){
                    Manifest.Permission.ReadExternalStorage,
                    Manifest.Permission.WriteExternalStorage,
                    Manifest.Permission.AccessCoarseLocation,
                    Manifest.Permission.AccessFineLocation,
                    Manifest.Permission.Bluetooth,
                    Manifest.Permission.BluetoothAdmin
            };
            
            foreach (string item in permissionList)
            {
                if (ContextCompat.CheckSelfPermission(this, item) != (int)Permission.Granted)
                {
                    RequestPermissions(new String[] {item }, 0);
                }
            }
        }

        private void btnConnectOnClick(object sender, EventArgs e)
        {
            //throw new NotImplementedException();
        }

        public override bool OnCreateOptionsMenu(IMenu menu)
        {
            MenuInflater.Inflate(Resource.Menu.menu_main, menu);
            return true;
        }

        public override bool OnOptionsItemSelected(IMenuItem item)
        {
            int id = item.ItemId;
            if (id == Resource.Id.action_settings)
            {
                return true;
            }

            return base.OnOptionsItemSelected(item);
        }

        private async void btnSearchOnClick(object sender, EventArgs eventArgs)
        {
            var text = FindViewById<AppCompatTextView>(Resource.Id.textView);

            var ble = CrossBluetoothLE.Current;
            var adapter = CrossBluetoothLE.Current.Adapter;
            var state = ble.State;

            //ble.StateChanged += (s, e) =>
            //{
            //    Debug.WriteLine($"The bluetooth state changed to {e.NewState}");
            //};

            List<Plugin.BLE.Abstractions.Contracts.IDevice> deviceList =new List<Plugin.BLE.Abstractions.Contracts.IDevice>();
            adapter.DeviceDiscovered += (s, a) => deviceList.Add(a.Device);
            await adapter.StartScanningForDevicesAsync();

            Thread.Sleep(10000);

            await adapter.StopScanningForDevicesAsync();

            foreach (Plugin.BLE.Abstractions.Contracts.IDevice item in deviceList)
            {
                text.Text += item.Name;
            }

        }

        public override void OnRequestPermissionsResult(int requestCode, string[] permissions, [GeneratedEnum] Android.Content.PM.Permission[] grantResults)
        {
            Xamarin.Essentials.Platform.OnRequestPermissionsResult(requestCode, permissions, grantResults);

            base.OnRequestPermissionsResult(requestCode, permissions, grantResults);
        }
	}
}
