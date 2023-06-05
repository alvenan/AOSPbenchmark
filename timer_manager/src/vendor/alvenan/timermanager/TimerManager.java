package vendor.alvenan.timermanager;

import android.util.Log;
import android.os.ServiceManager;
import android.os.IBinder;
import android.os.RemoteException;

import vendor.alvenan.timer.ITimer;

public class TimerManager {
    private IBinder binder;
    private ITimer service;

    private static TimerManager instance;

    private TimerManager() {
        binder = ServiceManager.getService("vendor.alvenan.timer.ITimer/default");
        if (binder != null) {
            service = ITimer.Stub.asInterface(binder);
            if (service != null)
                Log.d("TimerManager", "Serviço Timer acessado com sucesso.");
            else
                Log.e("TimerManager", "Erro ao acessar o serviço Timer!");
            }
        else
            Log.e("TimerManager", "Erro ao acessar o Binder!");
    }

    public static TimerManager getInstance() {
        if (instance == null)
            instance = new TimerManager();
        return instance;
    }

    public boolean isReady() throws RemoteException {
        return service.isReady();
    }

    public void trigger() throws RemoteException {
        service.trigger();
    }
}